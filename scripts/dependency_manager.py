import os
import shutil

class DependencyManager:
    def setup_glfw(self):
        if not os.path.exists("universe/vendor/glfw"):
            raise Exception("GLFW not found in vendor directory")

        # Copy the premake5.lua file
        premake_file = "scripts/glfw_premake5.lua"
        glfw_dir = "universe/vendor/glfw"
        destination = os.path.join(glfw_dir, "premake5.lua")
        shutil.copyfile(premake_file, destination)
        print(f"Copied {premake_file} to {destination}")

        # Add premake5.lua to the submodule's exclude file
        git_exclude_path = ".git/modules/universe/vendor/glfw/info/exclude"

        if not os.path.exists(git_exclude_path):
            os.makedirs(os.path.dirname(git_exclude_path), exist_ok=True)
            with open(git_exclude_path, "w") as exclude_file:
                exclude_file.write("# Git exclude file\n")

        with open(git_exclude_path, "r") as exclude_file:
            exclude_content = exclude_file.read()

        if "premake5.lua" not in exclude_content:
            with open(git_exclude_path, "a") as exclude_file:
                exclude_file.write("premake5.lua\n")
            print(f"Added 'premake5.lua' to {git_exclude_path}")
        else:
            print("'premake5.lua' is already excluded in the Git exclude file.")
