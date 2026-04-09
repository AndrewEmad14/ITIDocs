# Docker Revision Guide

> 📄 Full CLI Reference: [Docker CLI](https://docs.docker.com/reference/cli/docker/)

---

## Table of Contents

1. [Core Concepts](#1-core-concepts)
   - 1.1 [What is Docker?](#11-what-is-docker)
   - 1.2 [Containers vs Virtual Machines](#12-containers-vs-virtual-machines)
   - 1.3 [Docker Architecture](#13-docker-architecture)
   - 1.4 [Images & Layers](#14-images--layers)
   - 1.5 [Volumes & Persistence](#15-volumes--persistence)
2. [Dockerfile Instructions](#2-dockerfile-instructions)
   - 2.1 [RUN vs CMD vs ENTRYPOINT](#21-run-vs-cmd-vs-entrypoint)
   - 2.2 [EXPOSE vs -p (Port Mapping)](#22-expose-vs--p-port-mapping)
   - 2.3 [Layer Caching & Build Optimization](#23-layer-caching--build-optimization)
   - 2.4 [Multi-Stage Builds](#24-multi-stage-builds)
3. [Networking](#3-networking)
   - 3.1 [Default Bridge vs User-Defined Bridge](#31-default-bridge-vs-user-defined-bridge)
   - 3.2 [Port Mapping Deep Dive](#32-port-mapping-deep-dive)
4. [Lab Walkthroughs](#4-lab-walkthroughs)
   - 4.1 [Problem 1 — hello-world (Container Basics)](#41-problem-1--hello-world-container-basics)
   - 4.2 [Problem 2 — Interactive Containers](#42-problem-2--interactive-containers)
   - 4.3 [Problem 3 — MySQL Database](#43-problem-3--mysql-database)
   - 4.4 [Problem 4 — nginx with Volumes & Port Mapping](#44-problem-4--nginx-with-volumes--port-mapping)
5. [Image Tagging & Docker Hub](#5-image-tagging--docker-hub)
6. [Common Pitfalls](#6-common-pitfalls)
7. [Quick Reference Cheatsheet](#7-quick-reference-cheatsheet)
8. [Docker in development](#8-docker-in-development)


---

## 1. Core Concepts

### 1.1 What is Docker?

Docker packages an application and everything it needs to run — code, runtime, libraries, config — into a single unit called a **container**. That container runs identically on any machine.

> Think of it like an npm package — but instead of just code, it packages the entire runtime environment.

📖 [What is Docker?](https://docs.docker.com/get-started/docker-overview/)

---

### 1.2 Containers vs Virtual Machines

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

Containers use two Linux kernel features under the hood:
- **Namespaces** — isolate what a container can *see* (filesystem, network, processes)
- **cgroups** — limit what a container can *use* (CPU, memory, disk)

📖 [Containers vs VMs](https://docs.docker.com/get-started/docker-concepts/the-basics/what-is-a-container/)

---

### 1.3 Docker Architecture

Docker uses a **client-server** architecture:

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

| Component | Role |
|---|---|
| **Docker Client** | The `docker` command. Sends instructions to the daemon via REST API. |
| **Docker Daemon (`dockerd`)** | Background service that builds images, runs containers, manages volumes and networks. |
| **Docker Registry** | Where images are stored and shared. Docker Hub is the default — like npm but for images. |

📖 [Docker Architecture](https://docs.docker.com/get-started/docker-overview/#docker-architecture)

---

### 1.4 Images & Layers

A Docker image is a **read-only template** used to create containers.

```
Image      →  like a class definition / blueprint
Container  →  like a running instance of that class
```

Images are built in **layers** — each Dockerfile instruction adds a layer:

```
[ Layer 4: COPY app files     ]  ← your changes
[ Layer 3: RUN npm install    ]
[ Layer 2: COPY package.json  ]
[ Layer 1: FROM node:18       ]  ← base image
```

**Key traits:**
- Layers are **cached** — unchanged layers don't rebuild
- Images are **immutable** — you never modify one directly
- Multiple containers can share the same image simultaneously

```bash
docker images          # list local images
docker pull nginx      # pull from Docker Hub
docker rmi nginx       # remove a local image
```

📖 [Docker Images](https://docs.docker.com/get-started/docker-concepts/building-images/)

---

### 1.5 Volumes & Persistence

By default, any data written inside a container **disappears when it's removed** — containers are ephemeral by design. Volumes solve this.

**Named Volumes** — Docker manages the storage location:
```bash
docker run -v my-volume:/data nginx
```
- Docker decides where data lives on your host
- Data survives `docker rm`
- Best for: databases, production data

**Bind Mounts** — you point to a specific host folder:
```bash
docker run -v /your/host/folder:/data nginx
```
- You control the storage location
- Changes on host appear instantly inside the container
- Best for: config files, local development

```
Named Volume →  [ Docker managed storage ] ←→ [ Container ]
Bind Mount   →  [ Your host folder      ] ←→ [ Container ]
```

| Feature | Named Volume | Bind Mount |
|---|---|---|
| Host path control | ❌ Docker decides | ✅ You decide |
| Host folder must exist first | ❌ | ✅ |
| Edit files from host easily | ❌ Harder | ✅ Direct |
| Persists after `docker rm` | ✅ | ✅ |
| Portable across machines | ✅ | ❌ |
| Best for | Production data | Dev / config files |

📖 [Docker Storage](https://docs.docker.com/engine/storage/)

---

## 2. Dockerfile Instructions

### 2.1 RUN vs CMD vs ENTRYPOINT

These three are the most commonly confused instructions.

| Instruction | When it runs | Purpose |
|---|---|---|
| `RUN` | **Build time** | Install deps, set up image layers |
| `CMD` | **Run time** | Default command — fully replaceable at `docker run` |
| `ENTRYPOINT` | **Run time** | Locked executable — only args change |

**Example — CMD (replaceable):**
```dockerfile
FROM ubuntu
CMD ["echo", "hello"]
```
```bash
docker run myimage              # prints: hello
docker run myimage echo world   # prints: world  ← CMD replaced entirely
```

**Example — ENTRYPOINT (locked):**
```dockerfile
FROM ubuntu
ENTRYPOINT ["echo"]
CMD ["hello"]         # default arg
```
```bash
docker run myimage          # prints: hello
docker run myimage world    # prints: world  ← only arg replaced
```

**Combined pattern** (most flexible):
```dockerfile
ENTRYPOINT ["sleep"]
CMD ["5"]             # default: sleep 5
```
```bash
docker run myimage        # sleeps 5 seconds
docker run myimage 30     # sleeps 30 seconds
```

> ⚠️ Only the **last** `CMD` or `ENTRYPOINT` in a Dockerfile is used. Earlier ones are silently discarded.

📖 [CMD](https://docs.docker.com/reference/dockerfile/#cmd) | [ENTRYPOINT](https://docs.docker.com/reference/dockerfile/#entrypoint)

---

### 2.2 EXPOSE vs -p (Port Mapping)

| | What it does | Level |
|---|---|---|
| `EXPOSE 80` in Dockerfile | Documentation only — marks the intended port, opens nothing | Inside container |
| `-p 4200:80` in `docker run` | Actually binds host port to container port | Host ↔ Container |

```bash
# Format: -p <host-port>:<container-port>
docker run -p 4200:80 myimage
# Traffic to localhost:4200 on your machine → port 80 inside the container
```

> You need **`-p`** to actually expose a port. `EXPOSE` alone does nothing at runtime.

📖 [Published ports](https://docs.docker.com/engine/network/#published-ports)

---

### 2.3 Layer Caching & Build Optimization

Every Dockerfile instruction creates a cached layer. Docker skips rebuilding a layer if its inputs haven't changed. **Order matters.**

```dockerfile
# ✅ Optimized — npm install only reruns if package.json changes
COPY package*.json ./
RUN npm install
COPY . .
RUN npm run build

# ❌ Unoptimized — npm install reruns on EVERY code change
COPY . .
RUN npm install
RUN npm run build
```

> Put instructions that change least frequently at the **top**, and instructions that change most frequently at the **bottom**.

📖 [Layer caching](https://docs.docker.com/build/cache/)

---

### 2.4 Multi-Stage Builds

Use multiple `FROM` statements to separate build and runtime environments. The final image only contains what you explicitly copy — not the entire build toolchain.

```dockerfile
# Stage 1 — Build (large, disposable)
FROM node:20 AS builder
WORKDIR /app
COPY package*.json ./
RUN npm install
COPY . .
RUN npm run build

# Stage 2 — Serve (tiny, production-ready)
FROM nginx:latest
COPY --from=builder /app/dist/my-app/browser /usr/share/nginx/html
EXPOSE 80
```

| Stage | Base Image | Size | Kept? |
|---|---|---|---|
| Build | `node:20` | ~1 GB | ❌ Discarded |
| Serve | `nginx:latest` | ~50 MB | ✅ Final image |

```bash
docker build -t my-app .
docker run -p 4200:80 my-app
```

**Why it matters:** Your users never get your `node_modules`, build tools, or source code — only the compiled output served by nginx.

📖 [Multi-stage builds](https://docs.docker.com/build/building/multi-stage/)

---

## 3. Networking

### 3.1 Default Bridge vs User-Defined Bridge

Docker containers on the **default bridge network** cannot reach each other by name — only by IP address, which changes on every restart.

**Default bridge — containers use IPs:**
```bash
docker run -d --name db mysql
docker run -d --name app myapp
# app cannot ping "db" by name — must use its IP
```

**User-defined bridge — automatic DNS by container name:**
```bash
# Create a custom network
docker network create my-network

# Attach both containers to it
docker run -d --name db --network my-network mysql
docker run -d --name app --network my-network myapp

# Now app can reach db simply by name:
# mysql -h db -u root -p
```

| Feature | Default Bridge | User-Defined Bridge |
|---|---|---|
| Container DNS by name | ❌ | ✅ |
| Isolation | Shared | Per-network |
| Recommended for production | ❌ | ✅ |

```bash
docker network create <name>          # create network
docker network ls                     # list networks
docker network inspect <name>         # full details
docker run --network <name> <image>   # attach container
```

📖 [Bridge networking](https://docs.docker.com/engine/network/drivers/bridge/)

---

### 3.2 Port Mapping Deep Dive

Port mapping has two layers that must both be configured — common source of confusion:

```
Your host:8090  →  -p flag  →  container:8090  →  app listening on 8090
```

**For nginx specifically**, you must change the port in TWO places:

**1. nginx config (inside the container):**
```nginx
server {
    listen       8090;        # change from default 80
    listen  [::]:8090;        # don't forget IPv6
    server_name  localhost;
}
```

**2. docker run flag (outside the container):**
```bash
docker run -p 8090:8090 nginx
```

> Missing either one means it won't work. `listen 8090` without `-p 8090:8090` = port is open inside but unreachable from your host.

---

## 4. Lab Walkthroughs

### 4.1 Problem 1 — hello-world (Container Basics)

**Concepts:** Pulling images, checking status, starting stopped containers, cleanup.

```bash
# Run hello-world (auto-pulls if not local)
docker run hello-world

# See running containers
docker ps

# See ALL containers including stopped
docker ps -a

# Start a stopped container
docker start <container_id>

# Remove a stopped container
docker rm <container_id>

# Remove the image
docker rmi hello-world
```

> `docker run` = `docker pull` + `docker create` + `docker start` in one command.
> A container that finishes its task (like hello-world) **stops automatically** but is not deleted — you must `docker rm` it.
> You must `docker rm` a container before you can `docker rmi` its image.

---

### 4.2 Problem 2 — Interactive Containers

**Concepts:** Interactive mode, file isolation, ephemeral container data.

```bash
# Run ubuntu with an interactive shell
docker run -it ubuntu bash

# Inside the container:
echo docker
touch hello-docker
exit

# Clean up
docker stop <container_id>
docker rm <container_id>

# Or remove ALL stopped containers at once
docker container prune
```

| Flag | Meaning |
|---|---|
| `-i` | Keep STDIN open (interactive) |
| `-t` | Allocate a terminal (TTY) |
| `-it` | Both — gives you a live shell |

> The file `hello-docker` you created inside the container is **gone forever** after `docker rm`. It only existed in the container's writable layer, which is destroyed with the container. This is exactly why volumes exist.

---

### 4.3 Problem 3 — MySQL Database

**Concepts:** Detached mode, environment variables, named containers.

```bash
docker run -d \
  --name app-database \
  -e MYSQL_ROOT_PASSWORD=P4sSw0rd0! \
  mysql:latest
```

| Flag | Meaning |
|---|---|
| `-d` | Detached — runs in background |
| `--name` | Give the container a readable name |
| `-e` | Set an environment variable inside the container |
| `mysql:latest` | Image name : tag |

**Verify it's running:**
```bash
docker ps                              # should show app-database as Up
docker logs app-database               # check MySQL startup logs
docker exec -it app-database bash      # shell in to verify
```

> Always check the image's Docker Hub page for required `-e` environment variables.
> In production, pin to a specific version (`mysql:8.0`) instead of using `latest`.

---

### 4.4 Problem 4 — nginx with Volumes & Port Mapping

**Concepts:** Bind mounts, named volumes, committing images, data persistence.

#### Part A — Add HTML Files & Commit Image

```bash
# Run nginx
docker run -d --name my-nginx nginx

# Copy HTML files into the running container
docker cp ./index.html my-nginx:/usr/share/nginx/html/index.html

# Save the container state as a new image
docker commit my-nginx my-nginx-image
```

> `docker commit` is not the recommended production approach — Dockerfiles are preferred — but valid for lab use.

#### Part B — Named Volume + Bind Mount + Port 8090

**nginx file locations inside the container:**

| Purpose | Path |
|---|---|
| HTML files | `/usr/share/nginx/html/` |
| Site config | `/etc/nginx/conf.d/default.conf` |
| Main config | `/etc/nginx/nginx.conf` |
| Logs | `/var/log/nginx/` |

**Step-by-step:**

```bash
# Step 1 — Extract the default config to your host
docker run -d nginx
docker cp <container_id>:/etc/nginx/conf.d/default.conf ./default.conf

# Step 2 — Edit default.conf: change port 80 → 8090 in both listen lines

# Step 3 — Run with both volumes
docker run \
  -v vol-1:/usr/share/nginx/html \                        # named volume for HTML
  -v /full/host/path/default.conf:/etc/nginx/conf.d/default.conf \  # bind mount for config
  -p 8090:8090 \
  -d nginx

# Step 4 — Test
curl http://localhost:8090

# Step 5 — Delete the container
docker rm -f <container_id>

# Step 6 — Verify vol-1 persisted
docker volume inspect vol-1
sudo ls $(sudo docker volume inspect vol-1 --format '{{.Mountpoint}}')

# Step 7 — Create a new container reusing vol-1 (HTML files still there!)
docker run \
  -v vol-1:/usr/share/nginx/html \
  -v /full/host/path/default.conf:/etc/nginx/conf.d/default.conf \
  -p 8090:8090 \
  -d nginx
```

> ✅ Named volumes persist after `docker rm` — the HTML files in `vol-1` survive across containers.

---

## 5. Image Tagging & Docker Hub

Docker Hub requires images to follow the format: `username/imagename:tag`

**3-step push flow:**
```bash
# Step 1 — Authenticate
docker login

# Step 2 — Tag your image
docker tag my-local-image yourusername/my-app:v1.0

# Step 3 — Push to Docker Hub
docker push yourusername/my-app:v1.0
```

> `docker tag` creates an alias — the original image stays untouched.
> Always version your tags in production (`v1.0`, `v1.1`) rather than relying on `latest`.

📖 [docker push](https://docs.docker.com/reference/cli/docker/image/push/) | [docker tag](https://docs.docker.com/reference/cli/docker/image/tag/)

---

## 6. Common Pitfalls

| Pitfall | What Happens | Fix |
|---|---|---|
| Dockerfile case sensitivity | `DockerFile` fails on Linux | Rename to exactly `Dockerfile` |
| `ng` not found in container | `ng` isn't globally installed | Use `npx ng serve` or `node_modules/.bin/ng` |
| Running old container after rebuild | Container uses old image | `docker rm -f` old container, then `docker run` again |
| Angular SSR overwrites `index.html` | nginx serves SSR file, not browser file | Use custom nginx config pointing to `index.csr.html` |
| Browser caching | Old content shows after fixes | Test in incognito or hard refresh `Cmd+Shift+R` |
| `docker-credential-desktop` error | Leftover Docker Desktop config | Edit `~/.docker/config.json` → set `"credsStore": ""` |
| Only last CMD/ENTRYPOINT wins | Earlier ones silently discarded | Keep only one CMD/ENTRYPOINT |
| EXPOSE is documentation only | Port not actually open | Use `-p` to actually bind the port |
| Default bridge has no DNS | Containers can't reach each other by name | Use user-defined bridge network |
| Named volumes persist after `docker rm` | Volume isn't cleaned up automatically | Run `docker volume rm` explicitly |
| Build context bloat | Slow builds — everything sent to daemon | Use `.dockerignore` |
| Containers run as root by default | Security risk | Add `USER` instruction in Dockerfile |

**Fix for permission denied on `systemctl`:**
```bash
systemctl start docker
systemctl stop docker.socket
```

**Fix for `ng` not found:**
```dockerfile
# ❌ Fails
CMD ["ng", "serve"]

# ✅ Works
CMD ["npx", "ng", "serve", "--host", "0.0.0.0"]
```

**Fix for Angular SSR / nginx routing (404 on refresh):**
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

**Fix for `docker-credential-desktop` error:**
```bash
# Edit ~/.docker/config.json
# Change: "credsStore": "desktop"
# To:     "credsStore": ""
docker login
```

---

## 7. Quick Reference Cheatsheet

### Container Lifecycle
```bash
docker run <image>                    # run a container
docker run -it <image> bash           # interactive with shell
docker run -d <image>                 # run in background (detached)
docker run -d --name <name> <image>   # named background container
docker run --rm <image>               # auto-remove when done
docker start <container_id>           # start a stopped container
docker stop <container_id>            # graceful stop
docker stop -t 2 <container_id>       # stop with 2s timeout
docker kill <container_id>            # force stop immediately
docker rm <container_id>              # remove a stopped container
docker rm -f <container_id>           # force remove a running container
docker container prune                # remove ALL stopped containers
```

### Inspecting Containers
```bash
docker ps                             # running containers
docker ps -a                          # all containers (inc. stopped)
docker logs -f <container_id>         # follow live logs
docker exec -it <container_id> sh     # shell into a running container
docker exec -it <container_id> cat /path/to/file   # print a file
docker exec -it <container_id> ls /path/           # list files
docker inspect <container_id>         # full JSON metadata
```

### Images
```bash
docker build -t <name> .              # build from Dockerfile in current dir
docker build -t <name> -f <file> .    # build using specific Dockerfile name
docker images                         # list local images
docker pull <image>                   # pull from registry
docker rmi <image>                    # remove an image
docker commit <container> <name>      # save container state as image
docker tag <source> <user/name:tag>   # tag for Docker Hub
docker push <user/name:tag>           # push to Docker Hub
docker login                          # authenticate with Docker Hub
```

### Volumes
```bash
docker volume create <name>           # create a named volume
docker volume ls                      # list all volumes
docker volume inspect <name>          # inspect volume metadata
docker volume rm <name>               # delete a volume
sudo ls $(sudo docker volume inspect <name> --format '{{.Mountpoint}}')  # list contents
```

### Copying Files
```bash
docker cp <container>:/path/file ./file    # copy out of container
docker cp ./file <container>:/path/file    # copy into container
```

### Networking
```bash
docker network create <name>               # create user-defined network
docker network ls                          # list networks
docker network inspect <name>              # inspect network details
docker run --network <name> <image>        # attach container to network
```

### Cleanup
```bash
docker system prune                        # remove all unused resources
docker system df                           # show disk usage
docker rm $(docker ps -aq)                 # remove all stopped containers
```

---

### Dockerfile Instructions Reference

| Instruction | When | What it does |
|---|---|---|
| `FROM <image>` | Build | Set base image |
| `FROM <image> AS <name>` | Build | Named stage for multi-stage builds |
| `WORKDIR <path>` | Build | Set working directory inside container |
| `COPY <src> <dest>` | Build | Copy files from host into container |
| `COPY --from=<stage> <src> <dest>` | Build | Copy files from a previous build stage |
| `ADD <src> <dest>` | Build | Like COPY but supports URLs & tar extraction |
| `RUN <command>` | Build time | Execute shell command, creates a layer |
| `CMD ["exec", "arg"]` | Run time | Default command — fully replaceable |
| `ENTRYPOINT ["exec"]` | Run time | Fixed executable — only args change |
| `EXPOSE <port>` | Docs only | Documents which port the app uses |
| `ENV KEY=value` | Run time | Set environment variable |
| `ARG NAME=default` | Build time | Build-time variable |
| `USER <username>` | Run time | Run as non-root user |
| `HEALTHCHECK CMD <cmd>` | Run time | Container health check |

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
| Bridge networking | [docs.docker.com/engine/network/drivers/bridge](https://docs.docker.com/engine/network/drivers/bridge/) |
| Published ports | [docs.docker.com/engine/network/#published-ports](https://docs.docker.com/engine/network/#published-ports) |
| Docker CLI reference | [docs.docker.com/reference/cli/docker](https://docs.docker.com/reference/cli/docker/) |
| Docker Hub | [hub.docker.com](https://hub.docker.com) |
| node image | [hub.docker.com/_/node](https://hub.docker.com/_/node) |
| Docker Security | [docs.docker.com/engine/security](https://docs.docker.com/engine/security/) |

```markdown


## 8 Docker in development

This document summarizes the core concepts and workflows for using Docker during the development phase, specifically focused on Python/Django and general full-stack environments.

---

## 1. Why Use Docker in Development?
Even with `venv` and `requirements.txt`, Docker provides layers of consistency that virtual environments cannot.

* **System Dependencies:** Manages non-Python software (PostgreSQL, Redis, C-libraries) that `venv` ignores.
* **Environment Parity:** Eliminates "it works on my machine" bugs by ensuring the OS, libraries, and runtimes are identical for every team member.
* **Isolation:** Allows you to run different versions of databases (e.g., Postgres 12 vs 16) for different projects simultaneously without conflict.
* **Instant Onboarding:** New developers can start the entire stack with a single command.

---

## 2. Docker Compose vs. Multi-Stage Builds

| Feature | Docker Compose | Multi-Stage Builds |
| :--- | :--- | :--- |
| **File Type** | `docker-compose.yml` | `Dockerfile` |
| **Purpose** | Orchestrating multiple containers (App + DB) | Optimizing a single image for production |
| **Workflow** | Connecting services via a shared network | Discarding build-tools to reduce image size |
| **Primary Use** | Development / Integration Testing | CI/CD / Production Deployment |

---

## 3. Standard Django Development Workflow

### A. The Structure
```text
project_root/
├── Dockerfile           # Instructions for the Django container
├── docker-compose.yml   # Links Django to the Database
├── requirements.txt     # Python dependencies
└── app/                 # Source code
```

### B. The Dockerfile (Development)
```dockerfile
FROM python:3.11-slim
ENV PYTHONDONTWRITEBYTECODE 1
ENV PYTHONUNBUFFERED 1
WORKDIR /code
COPY requirements.txt /code/
RUN pip install -r requirements.txt
COPY . /code/
```

### C. The Docker Compose (The Orchestrator)
```yaml
services:
  db:
    image: postgres:15
    volumes:
      - postgres_data:/var/lib/postgresql/data
    environment:
      - POSTGRES_PASSWORD=secret

  web:
    build: .
    command: python manage.py runserver 0.0.0.0:8000
    volumes:
      - .:/code          # Enables live-reloading (hot reload)
    ports:
      - "8000:8000"
    depends_on:
      - db

volumes:
  postgres_data:
```

---

## 4. Essential CLI Cheat Sheet

| Command | Result |
| :--- | :--- |
| `docker-compose up` | Build and start the entire stack. |
| `docker-compose up -d` | Start services in the background. |
| `docker-compose exec web <cmd>` | Run a command (like migrations) inside the container. |
| `docker-compose logs -f` | View live logs from all services. |
| `docker-compose down` | Stop and remove containers/networks (cleans up). |

---

## 5. Key Takeaway
Use **Docker Compose** during development to manage your infrastructure and ensure live-reloading via **Volumes**. Use **Multi-stage builds** only when you are ready to ship the code to production to keep the final image slim and secure.
```