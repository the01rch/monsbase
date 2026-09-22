import json
import re
import time
import requests
from bs4 import BeautifulSoup

# ---------- Load moves.json ----------
with open("moves.json", "r", encoding="utf-8") as f:
    moves_data = json.load(f)

name_to_id = {}
for move in moves_data["moves"]:
    # Normalise: lowercase, strip, collapse spaces
    key = move["name"].strip().lower()
    key = re.sub(r"\s+", " ", key)         # collapse multiple spaces
    name_to_id[key] = move["id"]

# ---------- Load your UT Pokemon ----------
with open("mons_UT.json", "r", encoding="utf-8") as f:
    ut_data = json.load(f)

pokemon_list = ut_data["pokemon"]

# ---------- Helper: extract moves from wiki page ----------
def extract_moves_from_page(html):
    soup = BeautifulSoup(html, "html.parser")
    move_ids = set()

    # The wiki often has <table class="wikitable"> for move lists.
    # Look for tables that contain "Level" or "TM" in header.
    tables = soup.find_all("table", class_="wikitable")
    for table in tables:
        rows = table.find_all("tr")
        for row in rows:
            cells = row.find_all("td")
            if not cells:
                continue
            # The first cell often contains the move name (may have a link)
            move_cell = cells[0]
            link = move_cell.find("a")
            if link:
                move_name = link.get_text(strip=True)
            else:
                move_name = move_cell.get_text(strip=True)
            # Clean up
            move_name = move_name.strip().lower()
            move_name = re.sub(r"\s+", " ", move_name)
            if move_name in name_to_id:
                move_ids.add(name_to_id[move_name])
    return sorted(list(move_ids))

# ---------- Main loop ----------
for pokemon in pokemon_list:
    name = pokemon["name"]
    # Wiki URL: replace spaces with underscores, escape special chars
    wiki_name = name.replace(" ", "_").replace("'", "%27")  # basic
    url = f"https://pokemmo.shoutwiki.com/wiki/{wiki_name}"
    print(f"Fetching {name} from {url} ...")

    try:
        response = requests.get(url, timeout=10)
        if response.status_code != 200:
            print(f"  Failed: {response.status_code}")
            pokemon["moves"] = []
            continue
        moves = extract_moves_from_page(response.text)
        pokemon["moves"] = moves
        print(f"  Found {len(moves)} moves")
    except Exception as e:
        print(f"  Error: {e}")
        pokemon["moves"] = []

    # Be polite, don't hammer the server
    time.sleep(0.5)

# ---------- Save result ----------
with open("ut_with_moves.json", "w", encoding="utf-8") as f:
    json.dump(ut_data, f, indent=2)

print("Done! Saved to ut_with_moves.json")
