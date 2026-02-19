import os
import subprocess

# Color codes.
BOLD_RED = "\033[1;31m"
BOLD_GREEN = "\033[1;32m"
BOLD_YELLOW = "\033[1;33m"
BOLD_BLUE = "\033[1;34m"
BOLD_MAGENTA = "\033[1;34m"
BOLD_CYAN = "\033[1;36m"
RESET = "\033[0m"

# Test directory.
BIN_DIR = "./build/test_bin"

def run_binary(path):
    try:
        # Run binary, capture stdout+stderr
        result = subprocess.run(
            [path],
            stdout=subprocess.PIPE,
            stderr=subprocess.STDOUT,
            text=True,  # capture as string
            check=False # don't raise exception on non-zero exit
        )

        binary_file = path[2:]
        if result.returncode == 0:
            print(f"[{binary_file}] {BOLD_GREEN}Success!{RESET}")
        else:
            print(f"[{binary_file}] {BOLD_RED}Fail!{RESET}")
            print(f"  Exit code: {result.returncode}")
            if result.stdout:
                print("  Output:")
                print(result.stdout)

    except Exception as e:
        print(f"{binary_file}: {BOLD_RED} Exception caught!{RESET}")
        print(f"  Exception: {e}")


def main():
    # List all files in BIN_DIR
    for name in os.listdir(BIN_DIR):
        path = os.path.join(BIN_DIR, name)

        # Skip directories, only run files with execute permission
        if os.path.isfile(path) and os.access(path, os.X_OK):
            run_binary(path)


if __name__ == "__main__":
    main()

