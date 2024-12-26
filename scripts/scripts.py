import argparse
from build_manager import BuildManager
from dependency_manager import DependencyManager

if __name__ == "__main__":
    parser = argparse.ArgumentParser()
    parser.add_argument("-r", "--run", help="Run the project", action="store_true")
    parser.add_argument("-b", "--build", help="Build the project", action="store_true")
    parser.add_argument("-br", "--build-run", help="Build and run the project", action="store_true")
    parser.add_argument("-R", "--rebuild", help="Clean and build the project", action="store_true")
    parser.add_argument("-Rr", "--rebuild-run", help="Clean, build and run the project", action="store_true")
    parser.add_argument("--glfw", help="Setup GLFW dependency", action="store_true")
    parser.add_argument("--stb", help="Setup STB dependency", action="store_true")

    args = parser.parse_args()

    build_manager = BuildManager()
    dependency_manager = DependencyManager()

    if args.build:
        build_manager.build()
    elif args.build_run:
        build_manager.build()
        build_manager.run()
    elif args.run:
        build_manager.run()
    elif args.rebuild:
        build_manager.clean()
        build_manager.build()
    elif args.rebuild_run:
        build_manager.clean()
        build_manager.build()
        build_manager.run()
    elif args.glfw:
        dependency_manager.setup_glfw()
    elif args.stb:
        dependency_manager.setup_stb()
