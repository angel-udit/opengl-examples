
# This is free software released into the public domain.
# ÁRgB (angel.rodriguez@udit.es)

import json
import os
import shutil
import urllib.request
import zipfile

DOWNLOADS = "downloads"
ACCOUNT   = "angel-udit"
REPO      = "third-party"
LIBRARIES = [ "assimp", "glad", "glm", "half", "sdl3", "soil2" ]

def create_downloads_folder():
    if not os.path.exists(DOWNLOADS):
        os.makedirs(DOWNLOADS)

def remove_downloads_folder():
    if os.path.exists(DOWNLOADS):
        shutil.rmtree(DOWNLOADS)

def remove_previous_libraries():
    for library in LIBRARIES:
        if os.path.exists(library):
            print(f"Removing previous version of {library}")
            shutil.rmtree(library)

def fetch_latest_release_from_github():
    print(f"Fetching latest release of {ACCOUNT}/{REPO}\n")
    api_url = (f"https://api.github.com/repos/{ACCOUNT}/{REPO}/releases/latest")
    with urllib.request.urlopen(api_url) as response:
        return json.loads(response.read().decode())

def download_file_from_url(url, file_name):
    output_file_name = os.path.join(DOWNLOADS, file_name)
    print(f"\nDownloading from {url}")
    urllib.request.urlretrieve(url, output_file_name)
    print(f"Successfully downloaded {file_name}")
    return output_file_name

def extract_zip_file(file_path):
    print(f"Extracting {file_path}")
    with zipfile.ZipFile(file_path, 'r') as zip_ref:
        zip_ref.extractall(".")
    print("Extraction completed successfully")

def download_and_extract_libraries():
    try:
        data = fetch_latest_release_from_github()
        remove_previous_libraries()
        create_downloads_folder()
        for asset in data['assets']:
            name = asset['name']
            if name.partition('.')[0] in LIBRARIES:
                downloaded_file_path = download_file_from_url(asset['browser_download_url'], name)
                extract_zip_file(downloaded_file_path)
    except Exception as e:
        print(f"Failed to download the libraries: {e}")

def cleanup():
    remove_downloads_folder()

def main():

    try:
        download_and_extract_libraries()
    except Exception as e:
        print(f"Failed: {e}")

    cleanup()

    print("\nDone.")

if __name__ == "__main__":
    main()
