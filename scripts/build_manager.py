import subprocess
import os
import shutil

class BuildManager:
    def __init__(self):
        self.start_project = "Sandbox"

    def build(self):
        subprocess.run(("./vendor/premake/premake5-windows.exe", "gmake2"))
        subprocess.run(("mingw32-make", "config=debug"))

    def run(self):
        exe_path = os.path.join(".", "build", "bin", "Debug", f"{self.start_project}", f"{self.start_project}.exe")
        if not os.path.exists(exe_path):
            raise FileNotFoundError(f"Executable not found at {exe_path}. Did you build the project?")
        subprocess.run(exe_path, shell=True)

    def clean(self):
        if os.path.exists("build"):
            shutil.rmtree("build")
        print("Cleaned the build directory.")