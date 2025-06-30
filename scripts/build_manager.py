import subprocess
import os
import shutil

class BuildManager:
    def __init__(self):
        self.start_project = "Sandbox"
        self.is_windows = os.name == 'nt'
        self.binary_extension = ".exe" if self.is_windows else ""

    def build(self):
        if self.is_windows:
            subprocess.run(("./vendor/premake/premake5-windows.exe", "gmake"))
            subprocess.run(("C:\\mingw64\\bin\\mingw32-make", "config=debug"))
        else:
            subprocess.run(["./vendor/premake/premake5-linux", "gmake"])
            subprocess.run(["make", "config=debug"])

    def run(self):
        exe_path = os.path.join(
            ".", "build", "bin", "Debug", self.start_project,
            f"{self.start_project}{self.binary_extension}"
        )
        if not os.path.exists(exe_path):
            raise FileNotFoundError(f"Executable not found at {exe_path}. Did you build the project?")
        subprocess.run(exe_path, shell=self.is_windows)

    def clean(self):
        if os.path.exists("build"):
            shutil.rmtree("build")
        print("Cleaned the build directory.")