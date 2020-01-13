# MeubleTV

## Materiel

TODO

## Installation de l'OS sur le raspberry pi zero w

### Installation de Raspbian

Image ISO: https://downloads.raspberrypi.org/raspbian_lite_latest
Guide d'installation: https://www.raspberrypi.org/documentation/installation/installing-images/README.md

### Rendre accessible le raspberry pi

Dans le répertoire Boot, copier les fichier suivants:
- Un fichier vide nommé ssh
- Un fichier wpa_supplicant.conf

```
country=FR # Your 2-digit country code
ctrl_interface=DIR=/var/run/wpa_supplicant GROUP=netdev
network={
    ssid="wifiName"
    psk="wifiPassword"
    key_mgmt=WPA-PSK
}
```

### Autre paramétrages une fois connecté en ssh
```
raspi-config
```
- Configuration de la locale : fr_FR.UTF-8 UTF-8
- Configuration time zone : Europe > Paris
- Configuration Clavier: Generic / Orther > French
- Expand filesytem

## Installation de MeubleTV
```
wget -O- https://github.com/thelemax/MeubleTV/blob/master/config/install.sh | sudo bash
```
