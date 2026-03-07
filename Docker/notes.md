# Docker Full Lab Guide — Problems 1–4

> 📄 Full CLI Reference: [Docker CLI](https://docs.docker.com/reference/cli/docker/)

---

## Introduction to Docker

### What is Docker?

Docker is a platform that lets you package an application and everything it needs to run — code, runtime, libraries, config — into a single unit called a **container.** You can then run that container anywhere: your laptop, a teammate's machine, or a cloud server, and it behaves exactly the same.

> Think of it like an npm package — but instead of just code, it packages the entire runtime environment.

> 📄 Ref: [What is Docker?](https://docs.docker.com/get-started/docker-overview/)

---

### Container vs Virtual Machine

This is the most important mental model to get right early.

| | Virtual Machine | Container |
|---|---|---|
| Includes | Full OS + kernel + app | App + libraries only |
| Size | GBs | MBs |
| Startup time | Minutes | Milliseconds |
| Isolation | Hardware level | Process level |
| Overhead | Heavy | Lightweight |

**How a VM works:**
```
[ Your App ]
[ Guest OS  ]        ← full OS per VM
[ Hypervisor ]       ← emulates hardware
[ Host OS   ]
[ Hardware  ]
```

**How a Container works:**
```
[ App A ]  [ App B ]  [ App C ]
[  Container Runtime (Docker)  ]  ← shares the host kernel
[          Host OS             ]
[          Hardware            ]
```

> Containers are not VMs — they don't boot a full OS. Instead they use two Linux kernel features:
> - **Namespaces** → isolate what a container can *see* (filesystem, network, processes)
> - **cgroups** → limit what a container can *use* (CPU, memory, disk)

> 📄 Ref: [Containers vs VMs](https://docs.docker.com/get-started/docker-concepts/the-basics/what-is-a-container/)

---

### Docker Architecture

Docker uses a **client-server** architecture with three main components:

```
[ Docker CLI ]  ←——— you type commands here
      |
      | REST API
      ↓
[ Docker Daemon (dockerd) ]  ←——— does the actual work
      |
      ↓
[ Containers ] [ Images ] [ Volumes ] [ Networks ]
```

**Docker Client** — the `docker` command you type in your terminal. It just sends instructions to the daemon.

**Docker Daemon (`dockerd`)** — the background service that actually builds images, runs containers, manages volumes and networks.

**Docker Registry** — where images are stored and shared. Docker Hub is the default public registry — like npm but for container images.

> 📄 Ref: [Docker Architecture](https://docs.docker.com/get-started/docker-overview/#docker-architecture)

---

### Images

A Docker image is a **read-only template** used to create containers. Think of it like a class in OOP — the image is the class, the container is the instance.

```
Image  →  like a blueprint / class definition
Container  →  like a running instance of that class
```

Images are built in **layers** — each instruction in a Dockerfile adds a new layer on top of the previous one:

```
[ Layer 4: COPY app files     ]  ← your changes
[ Layer 3: RUN npm install    ]
[ Layer 2: COPY package.json  ]
[ Layer 1: FROM node:18       ]  ← base image
```

**Key traits:**
- Layers are cached — unchanged layers don't get rebuilt
- Images are immutable — you never modify an image directly
- Images are pulled from a registry (`docker pull`) or built locally (`docker build`)
- Multiple containers can run from the same image simultaneously

```bash
docker images                  # list local images
docker pull nginx              # pull from Docker Hub
docker rmi nginx               # remove a local image
```

> 📄 Ref: [Docker Images](https://docs.docker.com/get-started/docker-concepts/building-images/)

---

### Volumes

By default, any data written inside a container **disappears when the container is removed** — containers are ephemeral by design.

Volumes solve this by storing data **outside** the container lifecycle.

**There are two main types:**

**Named Volumes** — Docker manages where data lives on your host:
```bash
docker run -v my-volume:/data nginx
```
- Docker controls the storage location
- Data persists after `docker rm`
- Best for: databases, production data

**Bind Mounts** — you point to a specific folder on your host:
```bash
docker run -v /your/host/folder:/data nginx
```
- You control the storage location
- Changes on host reflect instantly inside container
- Best for: config files, local development

```
Named Volume →  [ Docker managed storage ] ←→ [ Container ]
Bind Mount   →  [ Your host folder      ] ←→ [ Container ]
```

> 📄 Ref: [Docker Storage](https://docs.docker.com/engine/storage/)

---

## Problem 1 — Container Basics (hello-world)

### Concepts Covered
- Pulling and running an image
- Checking container status
- Starting a stopped container
- Cleaning up containers and images

### Key Commands

```bash
# Run hello-world (pulls automatically if not local)
docker run hello-world

# Check container status (running only)
docker ps

# Check ALL containers including stopped
docker ps -a

# Start a stopped container
docker start <container_id>

# Remove a stopped container
docker rm <container_id>

# Remove the image
docker rmi hello-world
```

### What to Know
- `docker run` = `docker pull` + `docker create` + `docker start` in one command
- A container that finishes its task (like hello-world) stops automatically — it doesn't get deleted
- You must `docker rm` a container before you can `docker rmi` its image

> 📄 Ref: [docker run](https://docs.docker.com/reference/cli/docker/container/run/) · [docker rm](https://docs.docker.com/reference/cli/docker/container/rm/) · [docker rmi](https://docs.docker.com/reference/cli/docker/image/rm/)

---

## Problem 2 — Interactive Containers (ubuntu/centos)

### Concepts Covered
- Running containers in interactive mode
- Executing commands inside containers
- Container isolation — why files don't persist

### Key Commands

```bash
# Run ubuntu interactively
docker run -it ubuntu bash

# Inside the container — echo a string
echo docker

# Touch a file inside the container
touch hello-docker

# Exit the container
exit

# Stop and remove the container
docker stop <container_id>
docker rm <container_id>

# Remove ALL stopped containers at once
docker container prune
```

### Flags Explained

| Flag | Meaning |
|---|---|
| `-i` | Keep STDIN open (interactive) |
| `-t` | Allocate a terminal (TTY) |
| `-it` | Both together — gives you a live shell |

### Key Insight — File Isolation
When you created `hello-docker` inside the container and then deleted the container:

> *The file is gone forever — it only existed in the container's writable layer, which is destroyed with `docker rm`*

This is **by design** — containers are isolated and ephemeral. This is exactly why volumes exist (Problem 4).

> 📄 Ref: [docker exec](https://docs.docker.com/reference/cli/docker/container/exec/) · [Container isolation](https://docs.docker.com/get-started/docker-concepts/running-containers/)

---

## Problem 3 — Running a MySQL Database

### Concepts Covered
- Running a container in the background (`-d`)
- Setting environment variables (`-e`)
- Naming containers (`--name`)

### Key Command

```bash
docker run -d \
  --name app-database \
  -e MYSQL_ROOT_PASSWORD=P4sSw0rd0! \
  mysql:latest
```

### Flags Explained

| Flag | Meaning |
|---|---|
| `-d` | Detached — runs in background |
| `--name` | Give the container a readable name |
| `-e` | Set an environment variable inside the container |
| `mysql:latest` | Image name : tag |

### Verify It's Running

```bash
docker ps                              # should show app-database as Up
docker logs app-database               # check MySQL startup logs
docker exec -it app-database bash      # shell in to verify
```

### What to Know
- Many images require environment variables to configure themselves at startup
- Always check the image's Docker Hub page for required `-e` variables
- `latest` tag always pulls the newest version — in production, pin to a specific version (e.g. `mysql:8.0`)

> 📄 Ref: [Environment variables](https://docs.docker.com/reference/cli/docker/container/run/#env) · [MySQL Docker image](https://hub.docker.com/_/mysql)

---

## Problem 4 — nginx with Volumes & Port Mapping

### Concepts Covered
- Adding static HTML files to nginx
- Committing a container as an image
- Named volumes vs bind mounts
- Port mapping
- Data persistence across containers

---

### Part A — Add HTML Files & Commit Image

```bash
# Run nginx
docker run -d --name my-nginx nginx

# Copy HTML files into the running container
docker cp ./index.html my-nginx:/usr/share/nginx/html/index.html

# Commit the container as a new image
docker commit my-nginx IMAGE_NAME
```

> ⚠️ `docker commit` is not the recommended production approach — Dockerfiles are preferred. But it's valid for lab purposes.

> 📄 Ref: [docker commit](https://docs.docker.com/reference/cli/docker/container/commit/)

---

### Part B — Two Volumes + Port 8090

#### The Two Volume Types Used

**vol-1 — Named Volume (HTML files)**
- Docker manages the storage location
- Persists after container is deleted
- Auto-populated with nginx's default HTML on first run

**vol-2 — Bind Mount (nginx config)**
- You control the exact file on your host
- Edit from your host machine directly
- Must exist on host before running the container

---

#### nginx File Locations (Inside Container)

| Purpose | Path |
|---|---|
| HTML files | `/usr/share/nginx/html/` |
| Site config | `/etc/nginx/conf.d/default.conf` |
| Main config | `/etc/nginx/nginx.conf` |
| Logs | `/var/log/nginx/` |

---

#### Step-by-Step Workflow

**Step 1 — Get the config file onto your host**
```bash
# Run a plain nginx container
docker run -d nginx

# Copy the config out to your host
docker cp <container_id>:/etc/nginx/conf.d/default.conf \
  /your/host/folder/default.conf
```

**Step 2 — Edit the config on your host**
```nginx
server {
    listen       8090;        # change from 80
    listen  [::]:8090;        # change from 80 — don't forget IPv6!
    server_name  localhost;
    ...
}
```

**Step 3 — Run the container with both volumes**
```bash
docker run \
  -v vol-1:/usr/share/nginx/html \
  -v /full/host/path/default.conf:/etc/nginx/conf.d/default.conf \
  -p 8090:8090 \
  -d nginx
```

**Step 4 — Test the connection**
```bash
curl http://localhost:8090
# or open http://localhost:8090 in your browser
```

**Step 5 — Remove the container**
```bash
docker rm -f <container_id>
```

**Step 6 — Verify vol-1 persisted**
```bash
docker volume inspect vol-1
sudo ls $(sudo docker volume inspect vol-1 --format '{{.Mountpoint}}')
```

**Step 7 — Create new container reusing vol-1 + bind mount config**
```bash
docker run \
  -v vol-1:/usr/share/nginx/html \
  -v /full/host/path/default.conf:/etc/nginx/conf.d/default.conf \
  -p 8090:8090 \
  -d nginx
```

> ✅ HTML files from vol-1 are still there — named volumes persist!

---

### Port Mapping vs nginx `listen` — Critical Distinction

These are **two different things** at two different levels:

| | What it does | Level |
|---|---|---|
| `listen 8090` in config | Tells nginx which port to use | Inside container |
| `-p 8090:8090` in docker run | Opens a path from host into container | Outside container |

```
Your host:8090  →  -p flag  →  container:8090  →  nginx listening on 8090
```

> You need **both** — one without the other won't work.

> 📄 Ref: [Published ports](https://docs.docker.com/engine/network/#published-ports)

---

### Named Volume vs Bind Mount — Final Comparison

| Feature | Named Volume | Bind Mount |
|---|---|---|
| Host path control | ❌ Docker decides | ✅ You decide |
| Host folder must exist first | ❌ | ✅ |
| Edit files from host easily | ❌ Harder | ✅ Direct |
| Persists after `docker rm` | ✅ | ✅ |
| Portable across machines | ✅ | ❌ |
| Best for | Production data | Dev / config files |

---

## Full Commands Cheatsheet

### Container Lifecycle
```bash
docker run <image>                    # run a container
docker run -it <image> bash           # interactive with shell
docker run -d <image>                 # run in background
docker start <container_id>           # start a stopped container
docker stop <container_id>            # graceful stop
docker stop -t 2 <container_id>       # stop with 2s timeout
docker kill <container_id>            # force stop
docker rm <container_id>              # remove stopped container
docker rm -f <container_id>           # force remove running container
docker container prune                # remove ALL stopped containers
```

### Inspecting Containers
```bash
docker ps                             # running containers
docker ps -a                          # all containers
docker logs -f <container_id>         # follow live logs
docker exec -it <container_id> sh     # shell into container
docker inspect <container_id>         # full JSON metadata
```

### Images
```bash
docker pull <image>                   # pull image from registry
docker images                         # list local images
docker rmi <image>                    # remove image
docker commit <container> <name>      # save container as image
```

### Volumes
```bash
docker volume create vol-1            # create named volume
docker volume ls                      # list all volumes
docker volume inspect vol-1           # inspect volume metadata
docker volume rm vol-1                # delete a volume
sudo ls $(sudo docker volume inspect vol-1 --format '{{.Mountpoint}}')  # list contents
```

### Copying Files
```bash
docker cp <container>:/path/file ./file    # copy out of container
docker cp ./file <container>:/path/file    # copy into container
```

### Cleanup
```bash
docker system prune                   # remove all unused resources
docker system df                      # show disk usage
```

---

> 📄 References:
> [Docker Storage](https://docs.docker.com/engine/storage/) ·
> [Docker Networking](https://docs.docker.com/engine/network/) ·
> [Docker CLI](https://docs.docker.com/reference/cli/docker/) ·
> [Dockerfile Reference](https://docs.docker.com/reference/dockerfile/) ·
> [Docker Security](https://docs.docker.com/engine/security/)