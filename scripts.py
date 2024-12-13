import subprocess
import argparse
import shutil
import os

def build():
    subprocess.run(("./vendor/premake/premake5-windows.exe", "gmake2"))
    subprocess.run(("mingw32-make", "config=debug"))

def run():
    try:
        subprocess.run(("./build/bin/Debug/Forge/Forge.exe", "gmake2"))
    except FileNotFoundError:
        print("Build the project first")
        b = input("Do you want to build the project now? (y/n): ")
        if b == "y":
            build()
            run()

def clean():
    if os.path.exists("build"):
        shutil.rmtree("build")

if __name__ == "__main__":
    parser = argparse.ArgumentParser()
    parser.add_argument("-r", "--run", help="Run the project", action="store_true")
    parser.add_argument("-b", "--build", help="Build the project", action="store_true")
    parser.add_argument("-br", "--build-run", help="Build and run the project", action="store_true")
    parser.add_argument("-R", "--rebuild", help="Clean and build the project", action="store_true")
    parser.add_argument("-Rr", "--rebuild-run", help="Clean, build and run the project", action="store_true")

    
    args = parser.parse_args()

    if args.build:
        build()
    elif args.build_run:
        build()
        run()
    elif args.run:
        run()
    elif args.rebuild:
        clean()
        build()
    elif args.rebuild_run:
        clean()
        build()
        run()