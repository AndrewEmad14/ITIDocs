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




# Common error
if docker refuses to stop a process saying permission denied

 systemctl start docker
 systemctl stop docker.socket


## Commands Used

```bash
# Build an image from a Dockerfile in current directory
docker build -t <image-name> .

# Build using a specific Dockerfile name
docker build -t <image-name> -f DockerFile .

# Run a container with port mapping
docker run -p 4200:80 <image-name>

# Run a container and auto-remove it after it exits
docker run --rm <image-name> <command>

# Run a container in the background (detached)
docker run -d <image-name>

# List running containers
docker ps

# List all containers including stopped
docker ps -a

# List all images
docker images

# Shell into a running container
docker exec -it <container-id> bash
docker exec -it <container-id> sh

# Print a file inside a running container
docker exec -it <container-id> cat /path/to/file

# List files inside a running container
docker exec -it <container-id> ls /path/to/dir

# Force remove a running container
docker rm -f <container-id>

# Volume commands
docker volume create <volume-name>
docker volume ls
docker volume inspect <volume-name>
```

---

## Dockerfile Instructions Used

```dockerfile
# Base image to build from
FROM node:20
FROM nginx:latest
FROM node:20 AS builder          # named stage for multi-stage builds

# Set working directory inside container
WORKDIR /app

# Copy files from host into container
COPY package*.json ./            # copy package files only (cache optimization)
COPY . .                         # copy everything else

# Copy files between stages (multi-stage)
COPY --from=builder /app/dist/ecommerce-frontend/browser /usr/share/nginx/html

# Run a shell command during build
RUN npm install
RUN npm run build
RUN echo '...' > /etc/nginx/conf.d/default.conf

# Document which port the container listens on (informational only)
EXPOSE 80

# Default command to run when container starts
CMD ["npx", "ng", "serve", "--host", "0.0.0.0"]
```

---

## Key Concepts Learned

### Layer Caching
Every Dockerfile instruction creates a cached layer. Docker skips rebuilding a layer if its inputs haven't changed.

```dockerfile
# ✅ Optimized order — npm install only reruns if package.json changes
COPY package*.json ./
RUN npm install
COPY . .
RUN npm run build

# ❌ Unoptimized — npm install reruns on every code change
COPY . .
RUN npm install
RUN npm run build
```
📖 Ref: [Layer caching](https://docs.docker.com/build/cache/)

---

### EXPOSE vs -p
| | What it does |
|---|---|
| `EXPOSE 80` | Documentation only — marks intended port, opens nothing |
| `-p 4200:80` | Actually binds host port 4200 to container port 80 |

```bash
docker run -p <host-port>:<container-port> <image>
```
📖 Ref: [Published ports](https://docs.docker.com/engine/network/#published-ports)

---

### --host 0.0.0.0
`ng serve` binds to `localhost` by default — meaning it only accepts requests from inside the container itself. To make it reachable via `-p` port mapping:

```dockerfile
CMD ["npx", "ng", "serve", "--host", "0.0.0.0"]
```

nginx does this by default — no flag needed.

📖 Ref: [Docker networking](https://docs.docker.com/engine/network/)

---

### Multi-Stage Builds
Use multiple `FROM` instructions to separate build and serve concerns. The final image only contains what's needed to run — not to build.

```dockerfile
# Stage 1 — Build
FROM node:20 AS builder
WORKDIR /app
COPY package*.json ./
RUN npm install
COPY . .
RUN npm run build

# Stage 2 — Serve
FROM nginx:latest
COPY --from=builder /app/dist/ecommerce-frontend/browser /usr/share/nginx/html
EXPOSE 80
```

| Stage | Image | Size |
|---|---|---|
| Build | `node:20` | ~1GB (discarded) |
| Serve | `nginx:latest` | ~50MB ✅ |

📖 Ref: [Multi-stage builds](https://docs.docker.com/build/building/multi-stage/)

---

## Common Pitfalls & Issues Faced

### 1. Dockerfile case sensitivity
Docker looks for exactly `Dockerfile`. `DockerFile` will fail on Linux.
```bash
mv DockerFile Dockerfile
```

### 2. `ng` not found in container
`ng` is not globally installed inside the container — it lives in `node_modules/.bin`.
```dockerfile
# ❌ Fails
CMD ["ng", "serve"]

# ✅ Works
CMD ["npx", "ng", "serve", "--host", "0.0.0.0"]
# or
CMD ["node_modules/.bin/ng", "serve", "--host", "0.0.0.0"]
```

### 3. Running old container after rebuilding image
After `docker build`, always stop and remove the old container before running a new one. An old running container uses the old image — not the newly built one.
```bash
docker rm -f <old-container-id>
docker run -p 4200:80 frontend:latest
```

### 4. Angular SSR overwrites index.html
Angular SSR apps output two files:
- `index.html` — SSR version (for Node.js server)
- `index.csr.html` — CSR version (for browsers via nginx)

Nginx's default config looks for `index.html` — which is the SSR file, not the browser file. Fix with a custom nginx config:

```dockerfile
RUN echo 'server {
    listen 80;
    location / {
        root /usr/share/nginx/html;
        index index.csr.html;
        try_files $uri $uri/ /index.csr.html;
    }
}' > /etc/nginx/conf.d/default.conf
```

> `try_files` is also important for Angular routing — without it, refreshing on a route like `/products/123` returns 404.

### 5. Browser caching
After fixing container issues, the browser may still show old content from cache. Always test in a private/incognito window or hard refresh (`Cmd+Shift+R`).

### 6. docker-credential-desktop error
Happens when Docker Desktop was previously installed and left behind a broken credentials config.
```bash
# Edit ~/.docker/config.json
# Change "credsStore": "desktop" to "credsStore": ""
docker login
docker build -t <image> .
```

---

## References

| Topic | Link |
|---|---|
| Dockerfile reference | [docs.docker.com/reference/dockerfile](https://docs.docker.com/reference/dockerfile/) |
| Layer caching | [docs.docker.com/build/cache](https://docs.docker.com/build/cache/) |
| Multi-stage builds | [docs.docker.com/build/building/multi-stage](https://docs.docker.com/build/building/multi-stage/) |
| Storage overview | [docs.docker.com/engine/storage](https://docs.docker.com/engine/storage/) |
| Volumes | [docs.docker.com/engine/storage/volumes](https://docs.docker.com/engine/storage/volumes/) |
| Bind mounts | [docs.docker.com/engine/storage/bind-mounts](https://docs.docker.com/engine/storage/bind-mounts/) |
| Networking overview | [docs.docker.com/engine/network](https://docs.docker.com/engine/network/) |
| Published ports | [docs.docker.com/engine/network/#published-ports](https://docs.docker.com/engine/network/#published-ports) |
| Docker CLI reference | [docs.docker.com/reference/cli/docker](https://docs.docker.com/reference/cli/docker/) |
| node image (DockerHub) | [hub.docker.com/_/node](https://hub.docker.com/_/node) |
| Angular compatibility table | [angular.dev/reference/releases](https://angular.dev/reference/releases#actively-supported-versions) |

---

## Summary

### Commands Quick Reference

| Command | What it does |
|---|---|
| `docker build -t <name> .` | Build an image from a Dockerfile in current directory |
| `docker build -t <name> -f <file> .` | Build using a specific Dockerfile name |
| `docker run -p <host>:<container> <image>` | Run a container with port mapping |
| `docker run --rm <image> <cmd>` | Run a container and auto-remove it after it exits |
| `docker run -d <image>` | Run a container in the background |
| `docker ps` | List running containers |
| `docker ps -a` | List all containers including stopped |
| `docker images` | List all images |
| `docker exec -it <id> bash` | Shell into a running container |
| `docker exec -it <id> cat <file>` | Print a file inside a running container |
| `docker exec -it <id> ls <dir>` | List files inside a running container |
| `docker rm -f <id>` | Force remove a running container |
| `docker volume create <name>` | Create a named volume |
| `docker volume ls` | List all volumes |
| `docker volume inspect <name>` | Inspect a volume |
| `docker login` | Authenticate with DockerHub |

---

### Dockerfile Instructions Quick Reference

| Instruction | What it does | Ref |
|---|---|---|
| `FROM <image>` | Set the base image | [FROM](https://docs.docker.com/reference/dockerfile/#from) |
| `FROM <image> AS <name>` | Named stage for multi-stage builds | [Multi-stage](https://docs.docker.com/build/building/multi-stage/) |
| `WORKDIR <path>` | Set working directory inside container | [WORKDIR](https://docs.docker.com/reference/dockerfile/#workdir) |
| `COPY <src> <dest>` | Copy files from host into container | [COPY](https://docs.docker.com/reference/dockerfile/#copy) |
| `COPY --from=<stage> <src> <dest>` | Copy files from a previous build stage | [COPY --from](https://docs.docker.com/build/building/multi-stage/#use-multi-stage-builds) |
| `RUN <command>` | Execute a shell command during build | [RUN](https://docs.docker.com/reference/dockerfile/#run) |
| `CMD ["exec", "args"]` | Default command when container starts (overridable) | [CMD](https://docs.docker.com/reference/dockerfile/#cmd) |
| `ENTRYPOINT ["exec", "args"]` | Fixed command when container starts (not overridable) | [ENTRYPOINT](https://docs.docker.com/reference/dockerfile/#entrypoint) |
| `EXPOSE <port>` | Document which port the container listens on | [EXPOSE](https://docs.docker.com/reference/dockerfile/#expose) |
| `ENV <key>=<value>` | Set environment variable at runtime | [ENV](https://docs.docker.com/reference/dockerfile/#env) |
| `ARG <name>` | Set a build-time variable | [ARG](https://docs.docker.com/reference/dockerfile/#arg) |

# vim clipboard enable

quick one liner

apt update && apt install -y vim-gtk3 && echo "set clipboard=unnamedplus" >> ~/.vimrc

### Install Vim with clipboard support
RUN apt-get update && apt-get install -y vim-gtk3

### Create the config file automatically
RUN echo "set clipboard=unnamedplus" > /root/.vimrc