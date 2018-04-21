import sys

#pip install paramiko
import paramiko

ssh=paramiko.SSHClient()
ssh.set_missing_host_key_policy(paramiko.AutoAddPolicy())
ssh.connect("172.16.8.120",22,"niuhaitao", "880607")

stdin,stdout,stderr=ssh.exec_command("g++ -o temp temp.c")
lines= stderr.readlines()
if lines:
    for line in lines:
        print "[error]",line.encode("utf-8")

stdin,stdout,stderr=ssh.exec_command("/root/temp")
lines= stdout.readlines()
for line in lines:
    print line
ssh.exec_command("rm -f /root/temp.c /root/temp")

t.close()
ssh.close()
