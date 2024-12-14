import subprocess
import os
import shutil

class BuildManager:
    def build(self):
        subprocess.run(("./vendor/premake/premake5-windows.exe", "gmake2"))
        subprocess.run(("mingw32-make", "config=debug"))

    def run(self):
        subprocess.run(("./build/bin/Debug/Forge/Forge.exe", "gmake2"))

    def clean(self):
        if os.path.exists("build"):
            shutil.rmtree("build")
        print("Cleaned the build directory.")
