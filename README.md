# MeubleTV

## Mise en oeuvre matérielle

### Composants nécessaires

- 1x Raspberry pi zero w
- 1x microSD Card 8GO
- 1x Arduino uno
- 1x Alimentation 5V 30A
- 4x LED STRIP APA102

### Schéma de raccordement

![Schéma de Montage](/docs/schéma.png)

### Montage

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

### Paramétrage une fois connecté en ssh
```
sudo raspi-config

```
- 5 Interfacing Options > P6 Serial > No (login shell to be accessible over serial), Yes (Serial port hardware)
- 7 Advanced Options > A1 Expand Filesystem

- Configuration de la locale : fr_FR.UTF-8 UTF-8
- Configuration time zone : Europe > Paris
- Configuration Clavier: Generic / Orther > French

```
reboot
```

## Installation de MeubleTV
```
wget -O- https://raw.githubusercontent.com/thelemax/MeubleTV/master/config/install.sh | sudo bash
```
