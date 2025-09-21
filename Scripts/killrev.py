#!/usr/bin/env python3
import os
import subprocess
import time

def check_reverse_shells():
    print("Scanning for revshell...")

     
    try:
        output = subprocess.check_output(
            ["netstat", "-tnp"], stderr=subprocess.DEVNULL
        ).decode()

        suspicious = []

        for line in output.splitlines():
            if "ESTABLISHED" in line and "127.0.0.1" not in line:
                parts = line.split()
                if len(parts) >= 7:
                    proto, recv_q, send_q, local, remote, state, pid_prog = parts[:7]
                    pid, prog = pid_prog.split("/") if "/" in pid_prog else (pid_prog, "unknown")

                    #extract ip and port
                    remote_ip, remote_port = remote.rsplit(":", 1)
                    local_ip, local_port = local.rsplit(":", 1)

                    # flag if remote port is non-standard or remote ip is suspicious
                    if int(remote_port) > 1024:
                        suspicious.append((prog, pid, remote_ip, remote_port))

        if suspicious:
            print("\n[!] Potential reverse shells detected:")
            for prog, pid, ip, port in suspicious:
                print(f"  - PID {pid} ({prog}) ➜ {ip}:{port}")
        else:
            print("No outbound connections found.")
    
    except Exception as e:
        print(f"Error: {e}")

if __name__ == "__main__":
    check_reverse_shells()
