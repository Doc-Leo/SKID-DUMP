#!/usr/bin/env python3

import subprocess
import time
import os

# Store seen TTYs
seen_ttys = set()

def get_logged_in_users():
    try:
        output = subprocess.check_output(["who"]).decode()
        for line in output.strip().splitlines():
            parts = line.split()
            if len(parts) >= 5:
                username = parts[0]
                tty = parts[1]
                ip = parts[4]

                # If TTY is already seen, skip
                if tty in seen_ttys:
                    continue

                # New TTY detected
                seen_ttys.add(tty)
                print("=== New SSH Session Detected ===")
                print("User: {}\nTTY:  {}\nFrom: {}\n".format(username, tty, ip))

                # Show active processes on that TTY
                print("Active processes:")
                try:
                    ps_out = subprocess.check_output(["ps", "-t", tty, "-o", "pid,cmd"]).decode()
                    print(ps_out)
                except subprocess.CalledProcessError:
                    print("  Unable to fetch processes.\n")

                print("-" * 40)

    except Exception as e:
        print("Error: {}".format(e))

if __name__ == "__main__":
    while True:
        get_logged_in_users()
        time.sleep(5)  # Wait 5 seconds before checking again
