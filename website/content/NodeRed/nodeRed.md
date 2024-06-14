---
weight: 2
title: "Node Red setup"
---

# Node Red setup
## Notes on setting up Node Red
Node Red is quite finicky when it comes to git integration. Follow these steps to configure a SSH key and git.

Go inside docker container
```Bash
sudo docker exec -it nodered /bin/bash
```

Create SSH key. No password
```Bash
SSH-keygen -t rsa -b 4096 -C “email”
```

Start SSH agent
```Bash
eval $(ssh-agent)
```

Add SSH key
```Bash
ssh-add __default_nodered-iot
```

Set email and username
```Bash
git config --global user.name “username”
git config --global user.email “email”

Set upstream url
```Bash
git remote set-url origin “GITURL”
```

Test git connection:
```Bash
ssh git@github.com
git remote show origin
```