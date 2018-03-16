#!/usr/bin/expect -f

set pass "cg9wuuvp"
spawn scp -oStrictHostKeyChecking=no -oCheckHostIP=no execlineScript1.sh woong@lnxsrv.seas.ucla.edu:~/CS111/Lab1c/
expect "woong@lnxsrv.seas.ucla.edu's password: "
send "$pass\r"
interact
spawn scp -oStrictHostKeyChecking=no -oCheckHostIP=no execlineScript2.sh woong@lnxsrv.seas.ucla.edu:~/CS111/Lab1c/
expect "woong@lnxsrv.seas.ucla.edu's password: "
send "$pass\r"
interact
spawn scp -oStrictHostKeyChecking=no -oCheckHostIP=no execlineScript3.sh woong@lnxsrv.seas.ucla.edu:~/CS111/Lab1c/
expect "woong@lnxsrv.seas.ucla.edu's password: "
send "$pass\r"
interact
spawn scp -oStrictHostKeyChecking=no -oCheckHostIP=no execlineScript.sh woong@lnxsrv.seas.ucla.edu:~/CS111/Lab1c/
expect "woong@lnxsrv.seas.ucla.edu's password: "
send "$pass\r"
interact
spawn scp -oStrictHostKeyChecking=no -oCheckHostIP=no dashScript.sh woong@lnxsrv.seas.ucla.edu:~/CS111/Lab1c/
expect "woong@lnxsrv.seas.ucla.edu's password: "
send "$pass\r"
interact
spawn scp -oStrictHostKeyChecking=no -oCheckHostIP=no bashScript.sh woong@lnxsrv.seas.ucla.edu:~/CS111/Lab1c/
expect "woong@lnxsrv.seas.ucla.edu's password: "
send "$pass\r"
interact
spawn scp -oStrictHostKeyChecking=no -oCheckHostIP=no tcshScript.sh woong@lnxsrv.seas.ucla.edu:~/CS111/Lab1c/
expect "woong@lnxsrv.seas.ucla.edu's password: "
send "$pass\r"
interact
spawn scp -oStrictHostKeyChecking=no -oCheckHostIP=no simpshScript.sh woong@lnxsrv.seas.ucla.edu:~/CS111/Lab1c/
expect "woong@lnxsrv.seas.ucla.edu's password: "
send "$pass\r"
interact
spawn scp -oStrictHostKeyChecking=no -oCheckHostIP=no testAll.sh woong@lnxsrv.seas.ucla.edu:~/CS111/Lab1c/
expect "woong@lnxsrv.seas.ucla.edu's password: "
send "$pass\r"
interact



