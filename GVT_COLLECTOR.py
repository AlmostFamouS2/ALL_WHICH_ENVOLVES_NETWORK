#!/usr/bin/env python3
from os import name, system as sys
import subprocess
from requests import get

def banner():
	print("""
------------------------------------+
+       BY VITOR GUSMÃO              +
+        -- tool: GVT-COLLECTOR       +
+       $$ DISCORD: Nobody#9961        +
+       $$ INSTAGRAM: gusmaospeedcuber  +
+=======================================+
""")
print('Collecting... ')

def windows(ip, ip6=None):
    r=get(f"http://{ip}/cgi-bin/sophia_info.cgi")

    with open("k.txt","w") as f:
         f.write(r.text)
         f.close()

    wow=subprocess.getoutput('type k.txt |find "IP: "').splitlines()
    goal=subprocess.getoutput('type k.txt |find "Hostname"').splitlines()
    for l in range(0,len(wow),2):
        host=''.join(goal[l]).split()[4]
        host=''.join(host)
        print('\033[33m ==========> ',host,''.join(wow[l].split()[3:]),'\n\n')

if name=='nt':
    sys('color a')
    banner()
    
    add=subprocess.getoutput('arp -a |find "d" ').split()[5:]
    print("Gateway INFO: %s\n\n" %add[:2])
    windows(add[0])
    print('\033[0m')
    sys('del k.txt')
    exit(0)

sys("echo -e '\x1b[32m'")
banner()
ip=subprocess.getoutput('route -n |head -3 |tail -1 |cut -d "." -f4,5,6,7')
ip=ip.split()[1]
print(f"IP EH: {ip}")

content=subprocess.getoutput('curl -s http://{}/cgi-bin/sophia_info.cgi'.format(ip))

with open(".useless.txt","w") as f:
    f.write(content)
    f.close()

get=subprocess.getoutput('grep "IP: " .useless.txt |sort -u |cut -d ":" -f2').splitlines()
hst=subprocess.getoutput('grep "Hostname" .useless.txt |cut -d "=" -f2 ').splitlines()

for n in range(len(get)):
    print(hst[n],get[n][:-2])

sys('rm .useless.txt')
