import subprocess
import argparse
import shutil
import os

def build():
    subprocess.run(("./vendor/premake/premake5-windows.exe", "gmake2"))
    subprocess.run(("mingw32-make", "config=debug"))

def run():
    subprocess.run(("./build/bin/Debug/Forge/Forge.exe", "gmake2"))

def clean():
    if os.path.exists("build"):
        shutil.rmtree("build")

def setup_glfw():
    if not os.path.exists("universe/vendor/glfw"):
        raise Exception("GLFW not found in vendor directory")
    premake_file = "scripts/glfw_premake5.lua"
    glfw_dir = "universe/vendor/glfw"
    destination = os.path.join(glfw_dir, "premake5.lua")
    shutil.copyfile(premake_file, destination)

if __name__ == "__main__":
    parser = argparse.ArgumentParser()
    parser.add_argument("-r", "--run", help="Run the project", action="store_true")
    parser.add_argument("-b", "--build", help="Build the project", action="store_true")
    parser.add_argument("-br", "--build-run", help="Build and run the project", action="store_true")
    parser.add_argument("-R", "--rebuild", help="Clean and build the project", action="store_true")
    parser.add_argument("-Rr", "--rebuild-run", help="Clean, build and run the project", action="store_true")
    parser.add_argument("--glfw", help="Build GLFW", action="store_true")

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
    elif args.glfw:
        setup_glfw()