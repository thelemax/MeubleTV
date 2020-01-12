# MeubleTV


## Installation de l'environnement

### Installation de Raspbian

Image ISO: https://downloads.raspberrypi.org/raspbian_lite_latest
Guide d'installation: https://www.raspberrypi.org/documentation/installation/installing-images/README.md

### raspi-config
- Configuration de la locale : fr_FR.UTF-8 UTF-8
- Configuration time zone : Europe > Paris
- Configuration Clavier: Generic / Orther > French
- Activation du SSH (5 Interfacing Options > P2 SSH --> Yes)
- Expand filesytem

```
# Mise à jour des packages
sudo apt-get update
sudo apt-get dist-upgrade
```

### Configuration du WIFI
https://www.w3schools.com/nodejs/nodejs_raspberrypi.asp

Scan des réseaux wifi
```
sudo iwlist wlan0 scan
```

Ajout des du réseau dans le fichier `sudo nano /etc/wpa_supplicant/wpa_supplicant.conf` :
```
network={
  ssid="wifiName"
  psk="wifiPassword"
}
```

Redémarrage du rpi
```
sudo reboot
```

Vérification du paramètrage
```
ifconfig wlan0
# inet addr:192.168.1.50
```

### Installation node.js

```
curl -sL https://deb.nodesource.com/setup_10.x | sudo -E bash -
apt-get install -y nodejs

node -v
#Version node.js v10.13.0
```

### Installation de nginx
https://medium.com/@utkarsh_verma/configure-nginx-as-a-web-server-and-reverse-proxy-for-nodejs-application-on-aws-ubuntu-16-04-server-872922e21d38
sudo apt-get update && sudo apt-get upgrade -y
sudo apt-get install nginx -y

#### Configuration nginx

```
sudo apt-get update && sudo apt-get upgrade -y
sudo apt-get install nginx -y

sudo systemctl status nginx    # To check the status of nginx
sudo systemctl start nginx     # To start nginx

sudo systemctl enable nginx    # nginx au démarrage

sudo nano /etc/nginx/sites-available/default
```

```
server {
    listen 80;
    server_name your_domain.com;
    location / {
        proxy_pass http://127.0.0.1:8080;
        proxy_http_version 1.1;
        proxy_set_header Upgrade $http_upgrade;
        proxy_set_header Connection 'upgrade';
        proxy_set_header Host $host;
        proxy_cache_bypass $http_upgrade;
     }
}
```

```
sudo nginx -t                  # Verification que la configuration nginx est ok
sudo /etc/init.d/nginx reload  # Rechargement de nginx
```

### Installation de pm2

https://www.digitalocean.com/community/tutorials/how-to-set-up-a-node-js-application-for-production-on-ubuntu-16-04

### Installation Arduino Ligne de Commande
https://olivier.dossmann.net/2015/10/d%C3%A9velopper-pour-arduino-en-ligne-de-commande/


