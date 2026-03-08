Here are the important Apache directories and files to know:

## Config Files
| Path | Purpose |
|------|---------|
| `/etc/apache2/apache2.conf` | Main config file |
| `/etc/apache2/ports.conf` | Defines listening ports (default: 80, 443) |
| `/etc/apache2/envvars` | Environment variables (user, group, etc.) |

## Virtual Hosts
| Path | Purpose |
|------|---------|
| `/etc/apache2/sites-available/` | All defined virtual host configs |
| `/etc/apache2/sites-enabled/` | Active virtual hosts (symlinks to sites-available) |
| `/etc/apache2/sites-available/000-default.conf` | Default site config |

## Modules
| Path | Purpose |
|------|---------|
| `/etc/apache2/mods-available/` | All available modules |
| `/etc/apache2/mods-enabled/` | Currently loaded modules |

## Web Root
| Path | Purpose |
|------|---------|
| `/var/www/html/` | Default document root (your HTML files go here) |

## Logs
| Path | Purpose |
|------|---------|
| `/var/log/apache2/access.log` | All incoming requests |
| `/var/log/apache2/error.log` | Errors and warnings |

## Useful Commands
```bash
sudo a2ensite mysite.conf      # Enable a virtual host
sudo a2dissite mysite.conf     # Disable a virtual host
sudo a2enmod rewrite           # Enable a module
sudo a2dismod rewrite          # Disable a module
sudo apache2ctl configtest     # Test config for syntax errors
```

> **Note:** On CentOS/RHEL, replace `/etc/apache2/` with `/etc/httpd/` and `/var/log/apache2/` with `/var/log/httpd/`.

# Apache HTTP Server – Important Directives Reference

---

## 1. Core / General Directives

### `ServerName`
Sets the hostname and port that the server uses to identify itself.
```apache
ServerName www.example.com:80
```

### `ServerAdmin`
Email address of the server administrator, shown in error pages.
```apache
ServerAdmin webmaster@example.com
```

### `ServerRoot`
The top-level directory containing the server's config and log files.
```apache
ServerRoot "/etc/apache2"
```

### `DocumentRoot`
The directory from which Apache serves files.
```apache
DocumentRoot "/var/www/html"
```

### `Listen`
Tells Apache which IP address and port to listen on.
```apache
Listen 80
Listen 443
Listen 192.168.1.1:8080
```

### `Include` / `IncludeOptional`
Includes other configuration files.
```apache
Include /etc/apache2/sites-enabled/*.conf
IncludeOptional /etc/apache2/conf-enabled/*.conf
```

---

## 2. Directory & Access Control Directives

### `<Directory>`
Applies directives to a specific filesystem directory.
```apache
<Directory "/var/www/html">
    Options Indexes FollowSymLinks
    AllowOverride All
    Require all granted
</Directory>
```

### `<Files>`
Applies directives to specific files.
```apache
<Files "secret.txt">
    Require all denied
</Files>
```

### `<Location>`
Applies directives to a URL path (not filesystem).
```apache
<Location "/admin">
    Require ip 192.168.1.0/24
</Location>
```

### `Options`
Controls which server features are available in a directory.
```apache
Options Indexes FollowSymLinks MultiViews
# Indexes     = show directory listing if no index file
# FollowSymLinks = follow symbolic links
# ExecCGI     = allow CGI scripts
# None        = disable all options
```

### `AllowOverride`
Determines which directives in `.htaccess` files are allowed.
```apache
AllowOverride All         # allow everything in .htaccess
AllowOverride None        # ignore .htaccess completely
AllowOverride AuthConfig  # allow only auth-related directives
```

### `Require`
Controls access to resources (replaces old Allow/Deny).
```apache
Require all granted          # allow everyone
Require all denied           # deny everyone
Require ip 192.168.1.0/24   # allow specific IP range
Require user alice bob       # allow specific users
```

---

## 3. Virtual Host Directives

### `<VirtualHost>`
Defines a virtual host for name-based or IP-based hosting.
```apache
<VirtualHost *:80>
    ServerName example.com
    ServerAlias www.example.com
    DocumentRoot /var/www/example
    ErrorLog ${APACHE_LOG_DIR}/example-error.log
    CustomLog ${APACHE_LOG_DIR}/example-access.log combined
</VirtualHost>
```

### `ServerAlias`
Alternative names for a virtual host.
```apache
ServerAlias www.example.com example.net www.example.net
```

---

## 4. Redirect & Rewrite Directives

### `Redirect`
Redirects a URL to another URL (simple redirect).
```apache
# Temporary redirect (302)
Redirect /old-page.html /new-page.html

# Permanent redirect (301)
Redirect permanent /old-page.html /new-page.html

# Redirect entire old domain
Redirect permanent / https://www.newdomain.com/
```

### `RedirectMatch`
Like `Redirect` but uses regex patterns.
```apache
RedirectMatch permanent ^/blog/(.*)$ /articles/$1
```

### `RewriteEngine`
Enables or disables the rewrite engine (mod_rewrite).
```apache
RewriteEngine On
```

### `RewriteRule`
Rewrites requested URLs based on pattern matching.
```apache
# Redirect HTTP to HTTPS
RewriteEngine On
RewriteCond %{HTTPS} off
RewriteRule ^(.*)$ https://%{HTTP_HOST}%{REQUEST_URI} [L,R=301]
```

### `RewriteCond`
Defines a condition that must be met before a `RewriteRule` applies.
```apache
# Only rewrite if the request is NOT for an existing file
RewriteCond %{REQUEST_FILENAME} !-f
RewriteCond %{REQUEST_FILENAME} !-d
RewriteRule ^(.*)$ /index.php?path=$1 [QSA,L]
```

### `Alias`
Maps a URL path to a filesystem path outside DocumentRoot.
```apache
Alias /images /var/data/images
<Directory "/var/data/images">
    Require all granted
</Directory>
```

---

## 5. Authentication Directives

### `AuthType`
Specifies the type of authentication.
```apache
AuthType Basic
```

### `AuthName`
Sets the realm name shown in the browser login dialog.
```apache
AuthName "Restricted Area"
```

### `AuthUserFile`
Path to the password file created with `htpasswd`.
```apache
AuthUserFile /etc/apache2/.htpasswd
```

### Full Basic Auth Example
```apache
<Directory "/var/www/html/private">
    AuthType Basic
    AuthName "Members Only"
    AuthUserFile /etc/apache2/.htpasswd
    Require valid-user
</Directory>
```

---

## 6. Logging Directives

### `ErrorLog`
Specifies the file where Apache logs errors.
```apache
ErrorLog ${APACHE_LOG_DIR}/error.log
```

### `LogLevel`
Controls the verbosity of the error log.
```apache
LogLevel warn    # Options: emerg, alert, crit, error, warn, notice, info, debug
```

### `CustomLog`
Specifies the file and format for access logging.
```apache
CustomLog ${APACHE_LOG_DIR}/access.log combined
```

### `LogFormat`
Defines a named log format.
```apache
LogFormat "%h %l %u %t \"%r\" %>s %b" common
LogFormat "%h %l %u %t \"%r\" %>s %b \"%{Referer}i\" \"%{User-Agent}i\"" combined
```

---

## 7. Performance & Timeout Directives

### `Timeout`
Time (in seconds) Apache waits for requests and responses.
```apache
Timeout 300
```

### `KeepAlive`
Enables persistent connections (one TCP connection for multiple requests).
```apache
KeepAlive On
```

### `MaxKeepAliveRequests`
Maximum number of requests per persistent connection.
```apache
MaxKeepAliveRequests 100
```

### `KeepAliveTimeout`
Seconds to wait for the next request on a persistent connection.
```apache
KeepAliveTimeout 5
```

---

## 8. MIME & Content Directives

### `AddType`
Maps a file extension to a MIME type.
```apache
AddType application/x-httpd-php .php
AddType image/svg+xml .svg
```

### `DefaultType`
Sets the default MIME type for unknown file types.
```apache
DefaultType application/octet-stream
```

### `DirectoryIndex`
Defines which file to serve when a directory is requested.
```apache
DirectoryIndex index.html index.php index.htm
```

---

## 9. SSL / HTTPS Directives

### `SSLEngine`
Enables SSL/TLS for a virtual host.
```apache
SSLEngine on
```

### `SSLCertificateFile`
Path to the SSL certificate file.
```apache
SSLCertificateFile /etc/ssl/certs/example.crt
```

### `SSLCertificateKeyFile`
Path to the SSL private key file.
```apache
SSLCertificateKeyFile /etc/ssl/private/example.key
```

### Full HTTPS Virtual Host Example
```apache
<VirtualHost *:443>
    ServerName example.com
    DocumentRoot /var/www/html

    SSLEngine on
    SSLCertificateFile    /etc/ssl/certs/example.crt
    SSLCertificateKeyFile /etc/ssl/private/example.key

    ErrorLog  ${APACHE_LOG_DIR}/ssl-error.log
    CustomLog ${APACHE_LOG_DIR}/ssl-access.log combined
</VirtualHost>
```

---

## 10. .htaccess Directives

`.htaccess` files allow per-directory config without editing the main config. Common directives used inside them:

```apache
# Deny access to a file
<Files "config.php">
    Require all denied
</Files>

# Custom error pages
ErrorDocument 404 /errors/404.html
ErrorDocument 500 /errors/500.html

# Enable rewriting
RewriteEngine On
RewriteRule ^old-url$ /new-url [R=301,L]

# Redirect to HTTPS
RewriteCond %{HTTPS} off
RewriteRule ^ https://%{HTTP_HOST}%{REQUEST_URI} [L,R=301]

# Protect against directory listing
Options -Indexes

# Set default charset
AddDefaultCharset UTF-8
```

> ⚠️ `.htaccess` requires `AllowOverride All` in the server config to take effect.

---

## Quick Reference Table

| Directive | Purpose |
|-----------|---------|
| `ServerName` | Set hostname |
| `DocumentRoot` | Set web root folder |
| `Listen` | Set port to listen on |
| `Redirect` | Simple URL redirect |
| `RewriteRule` | Advanced URL rewriting |
| `Alias` | Map URL to filesystem path |
| `Require` | Access control |
| `AuthType` | Enable authentication |
| `DirectoryIndex` | Default index file |
| `ErrorLog` | Error log location |
| `CustomLog` | Access log location |
| `SSLEngine` | Enable HTTPS |
| `AllowOverride` | Control .htaccess usage |
| `Options` | Enable/disable features per directory |

---

## Final Example: Complete Virtual Host Config

A realistic production-style config for a site called `example.com` that covers most of the directives in this document.

```apache
# /etc/apache2/sites-available/example.com.conf

# ─── HTTP: Redirect all traffic to HTTPS ─────────────────────────────────────
<VirtualHost *:80>
    ServerName  example.com
    ServerAlias www.example.com
    ServerAdmin webmaster@example.com

    # Permanently redirect all HTTP requests to HTTPS
    Redirect permanent / https://example.com/
</VirtualHost>

# ─── HTTPS: Main site config ─────────────────────────────────────────────────
<VirtualHost *:443>
    ServerName  example.com
    ServerAlias www.example.com
    ServerAdmin webmaster@example.com

    # Web root
    DocumentRoot /var/www/example.com/public

    # SSL
    SSLEngine on
    SSLCertificateFile    /etc/ssl/certs/example.com.crt
    SSLCertificateKeyFile /etc/ssl/private/example.com.key

    # Default index files
    DirectoryIndex index.php index.html

    # ── Main directory settings ──────────────────────────────────────────────
    <Directory "/var/www/example.com/public">
        Options -Indexes +FollowSymLinks
        AllowOverride All
        Require all granted
    </Directory>

    # ── Serve uploads from outside DocumentRoot ──────────────────────────────
    Alias /uploads /var/data/example-uploads
    <Directory "/var/data/example-uploads">
        Options -Indexes
        Require all granted
    </Directory>

    # ── Protect sensitive files ───────────────────────────────────────────────
    <Files ~ "\.(env|log|sql|bak)$">
        Require all denied
    </Files>

    # ── Restrict /admin to local network only ─────────────────────────────────
    <Location "/admin">
        AuthType Basic
        AuthName "Admin Panel"
        AuthUserFile /etc/apache2/.htpasswd
        Require valid-user
    </Location>

    # ── URL rewriting (mod_rewrite) ───────────────────────────────────────────
    RewriteEngine On

    # Route all requests to index.php (front controller pattern)
    RewriteCond %{REQUEST_FILENAME} !-f
    RewriteCond %{REQUEST_FILENAME} !-d
    RewriteRule ^(.*)$ /index.php?url=$1 [QSA,L]

    # ── MIME types ────────────────────────────────────────────────────────────
    AddType application/x-httpd-php .php
    AddType image/svg+xml           .svg

    # ── Custom error pages ────────────────────────────────────────────────────
    ErrorDocument 403 /errors/403.html
    ErrorDocument 404 /errors/404.html
    ErrorDocument 500 /errors/500.html

    # ── Logging ───────────────────────────────────────────────────────────────
    LogLevel warn
    ErrorLog  ${APACHE_LOG_DIR}/example.com-error.log
    CustomLog ${APACHE_LOG_DIR}/example.com-access.log combined

</VirtualHost>
```

### Enable & test this config
```bash
sudo a2ensite example.com.conf      # enable the site
sudo apache2ctl configtest          # check for syntax errors
sudo systemctl reload apache2       # apply changes
sudo apache2ctl configtest          # test config files
```


## Goal: Protect a directory with a username & password

---

**1. Install apache2-utils** (needed to hash passwords):
```bash
sudo apt install apache2-utils
```

**2. Create the password file:**
```bash
sudo htpasswd -c /etc/apache2/.htpasswd alice
```

**3. Enable AllowOverride in your main config** (so Apache respects `.htaccess`):
```apache
<Directory "/var/www/html">
    AllowOverride All
</Directory>
```

**4. Create `.htaccess` inside the directory you want to protect:**
```apache
AuthType Basic
AuthName "Restricted Area"
AuthUserFile /etc/apache2/.htpasswd
Require valid-user
```

**5. Restart Apache:**
```bash
sudo systemctl restart apache2
```

---

## What each piece does

| Piece | Role |
|-------|------|
| `apache2-utils` | Hashes the password into a format Apache understands |
| `.htpasswd` | Stores the hashed username & password |
| `AllowOverride All` | Tells Apache to read and respect `.htaccess` |
| `AuthType Basic` | Use browser's built-in login popup |
| `AuthName` | The message shown on the login dialog |
| `AuthUserFile` | Points Apache to the password file |
| `Require valid-user` | Only let in users who exist in the password file |

Now visiting `http://localhost/private` will prompt for a login before granting access.