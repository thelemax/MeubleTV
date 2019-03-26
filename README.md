# MeubleTV


## Installation de l'environnement

### Installation de Raspbian

Image ISO: https://downloads.raspberrypi.org/raspbian_lite_latest
Guide d'installation: https://www.raspberrypi.org/documentation/installation/installing-images/README.md

### raspi-config
Configuration de la locale : fr_FR.UTF-8 UTF-8
Configuration time zone : Europe > Paris
Configuration Clavier: Generic / Orther > French
Activation du SSH (5 Interfacing Options > P2 SSH --> Yes)
Expand filesytem

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

### Installation de PM2
https://www.digitalocean.com/community/tutorials/how-to-set-up-a-node-js-application-for-production-on-ubuntu-16-04

### Installation Arduino Ligne de Commande
https://olivier.dossmann.net/2015/10/d%C3%A9velopper-pour-arduino-en-ligne-de-commande/


