#!/bin/sh
VERT="\\033[1;32m"
NORMAL="\\033[0;39m"
ROUGE="\\033[1;31m"
ROSE="\\033[1;35m"
BLEU="\\033[1;34m"
BLANC="\\033[0;02m"
BLANCLAIR="\\033[1;08m"
JAUNE="\\033[1;33m"
CYAN="\\033[1;36m"

#Verification root mode
if [ $(id -u) != 0 ] ; then
  echo "Les droits de super-utilisateur (root) sont requis pour installer MeubleTV"
  echo "Veuillez lancer 'sudo $0' ou connectez-vous en tant que root, puis relancez $0"
  exit 1
fi

#Commande apt-get install
apt_install() {
  apt-get -y install "$@"
  if [ $? -ne 0 ]; then
    echo "${ROUGE}Ne peut installer $@ - Annulation${NORMAL}"
    exit 1
  fi
}

#Désinstallation du programme
step_uninstall() {
  echo "---------------------------------------------------------------------"
  echo "${JAUNE}Désinstallation des programmes ${VERSION}${NORMAL}"
  #desinstallation nginx
  apt -y remove nginx
  rm -rf /etc/nginx
  rm -f /etc/systemd/system/node.service
  echo "${VERT}étape Désinstallation de la révision réussie${NORMAL}"
}

#Mise à jour des librairies
step_1_upgrade() {
  echo "---------------------------------------------------------------------"
  echo "${JAUNE}Commence l'étape 1 de la révision ${VERSION}${NORMAL}"
  apt-get update
  apt-get -f install
  apt-get -y dist-upgrade
  echo "${VERT}étape 1 de la révision réussie${NORMAL}"
}

#Installation des packages principaux
step_2_packages() {
  echo "---------------------------------------------------------------------"
  echo "${JAUNE}Commence l'étape 2 paquets${NORMAL}"

  echo "${JAUNE}Paquets principaux${NORMAL}"
  apt_install ntp ca-certificates unzip curl sudo cron
  apt-get -y install locate tar telnet wget logrotate fail2ban dos2unix ntpdate htop iotop vim iftop smbclient
  apt-get -y install git nano

  #Installation nginx
  echo "${JAUNE}nginx${NORMAL}"
  apt_install nginx
  
  #Installation nodejs
  echo "${JAUNE}nodejs${NORMAL}"
  #curl -sL https://deb.nodesource.com/setup_10.x | sudo -E bash -
  apt_install nodejs npm
  
  echo "${CYAN}nodejs version :${NORMAL}"
  node -v
  
  echo "${CYAN}npm version :${NORMAL}"
  npm -vs

  #Installation arduino
  echo "${JAUNE}arduino{NORMAL}"
  apt_install arduino-core arduino-mk
  
  echo "${VERT}étape 2 paquets réussie${NORMAL}"
}

#Récupération des sources
step_3_recupSources() {
 echo "---------------------------------------------------------------------"
 echo "${JAUNE}Commence l'étape 3 récuperation Sources${NORMAL}"

 wget --no-check-certificate https://github.com/thelemax/MeubleTV/archive/${VERSION}.zip -O /tmp/meubletv.zip

 if [ $? -ne 0 ]; then
   echo "${ROUGE}Ne peut télécharger MeubleTV depuis github.Annulation${NORMAL}"
   exit 1
 fi
 if [ ! /tmp/meubletv.zip ]; then
   echo "${ROUGE}Ne peut trouver l'archive MeubleTV.zip - Annulation${NORMAL}"
   exit 1
 fi

 unzip -o -q /tmp/meubletv.zip -d $PWD
 if [ $? -ne 0 ]; then
   echo "${ROUGE}Ne peut décompresser l'archive - Annulation${NORMAL}"
   exit 1
 fi

 rm /tmp/meubletv.zip
 chmod -R 777 ${REP_ROOT}/MeubleTV-${VERSION}

 echo "${VERT}étape 3 récuperation sources réussie${NORMAL}" 
}

#Installation programme arduino
step_4_install_arduino(){
  echo "---------------------------------------------------------------------"
  echo "${JAUNE}Commence l'étape 4 configuration arduino${NORMAL}"

  if [ -d ${REP_ROOT}/MeubleTV-${VERSION} ]; then

	  echo "${CYAN}Paramétrage des variables d'environnement arduino${NORMAL}"
	  export ARDUINO_DIR="/usr/share/arduino"
	  export ARDMK_DIR="/usr/share/arduino"
	  export AVR_TOOLS_DIR="/usr"
	  export ISP_PORT="/dev/ttyACM0"
  
	  echo "${CYAN}Recuperation de FastLED-${FASTLED_VERSION}${NORMAL}"
	  #/usr/share/arduino/libraries

	  wget --no-check-certificate https://github.com/FastLED/FastLED/archive/${FASTLED_VERSION}.zip -O /tmp/FastLED-${FASTLED_VERSION}.zip
	  #https://github.com/FastLED/FastLED/archive/master.zip
	  #https://github.com/FastLED/FastLED/archive/3.3.2.zip

	  if [ $? -ne 0 ]; then
		echo "${ROUGE}Ne peut télécharger FastLED depuis github.Annulation${NORMAL}"
		exit 1
	  fi
	  if [ ! /tmp/FastLED-${FASTLED_VERSION}.zip ]; then
		echo "${ROUGE}Ne peut trouver l'archive FastLED.zip - Annulation${NORMAL}"
		exit 1
	  fi

	  unzip -q /tmp/FastLED-${FASTLED_VERSION}.zip -d /tmp/
	  if [ $? -ne 0 ]; then
		echo "${ROUGE}Ne peut décompresser l'archive - Annulation${NORMAL}"
		exit 1
	  fi
	  rm -r /usr/share/arduino/libraries/FastLED
	  cp -r /tmp/FastLED-${FASTLED_VERSION} /usr/share/arduino/libraries/FastLED
  
	  rm /tmp/FastLED-${FASTLED_VERSION}.zip
	  rm -r /tmp/FastLED-${FASTLED_VERSION}
  
	  echo "${CYAN}Recuperation de avrdude.conf${NORMAL}"
	  cp -n ${REP_ROOT}/MeubleTV-${VERSION}/config/arduino/avrdude.conf /etc/avrdude.conf

	  echo "${CYAN}Compilation et Téléversement du programme arduino${NORMAL}"
      cp -rf ${REP_ROOT}/MeubleTV-${VERSION}/arduino-dev /var/opt/arduino
	  
	  cd /var/opt/arduino
      make
      sh upload.sh
  else
	  echo "${ROUGE}Repertoire introuvable${NORMAL}"
  fi
  echo "${VERT}étape 4 arduino réussi${NORMAL}" 
}

#Installation nginx
step_5_install_nginx() {
  echo "---------------------------------------------------------------------"
  echo "${JAUNE}Commence l'étape 5 nginx${NORMAL}"
     
  echo "${CYAN}Paramètrage de nginx${NORMAL}"
  if [ -d ${REP_ROOT}/MeubleTV-${VERSION} ]; then
   cp -f ${REP_ROOT}/MeubleTV-${VERSION}/config/nginx/serveur.conf /etc/nginx/sites-available/nginx-serveur.conf

   nginx -t

   # echo "Check the status of nginx"
   # systemctl status nginx
   echo "${CYAN}Start nginx${NORMAL}"
   systemctl status nginx > /dev/null 2>&1
   if [ $? -ne 0 ]; then
    service nginx status
    if [ $? -ne 0 ]; then
      systemctl start nginx > /dev/null 2>&1
      if [ $? -ne 0 ]; then
        service nginx start > /dev/null 2>&1
      fi
    fi
   fi
   systemctl status nginx > /dev/null 2>&1
   if [ $? -ne 0 ]; then
    service nginx status
    if [ $? -ne 0 ]; then
      echo "${ROUGE}Ne peut lancer nginx - Annulation${NORMAL}"
      exit 1
    fi
   fi
   echo "${CYAN}Enable nginx au démarrage${NORMAL}"
   systemctl enable nginx 
   #/etc/init.d/nginx reload
  else
   echo "${ROUGE}Repertoire introuvable${NORMAL}"
  fi
  echo "${VERT}étape 5 nginx réussie${NORMAL}" 
}

#Installation du programme nodejs
step_6_install_nodejs(){
 echo "${CYAN}Commence l'étape 6 nodejs${NORMAL}"
 
 if [ -d ${REP_ROOT}/MeubleTV-${VERSION} ]; then
  cp -rf ${REP_ROOT}/MeubleTV-${VERSION}/nodejs-dev /var/www/app

  cd /var/www/app/
  npm install --unsafe-perm --info -g sails
  node meuble-tv.js

  cp -n ${REP_ROOT}/MeubleTV-${VERSION}/config/nodejs/node.service  /etc/systemd/system/node.service

  echo "Check the status of node"
  systemctl status node
  echo "${CYAN}Start node{NORMAL}"

  systemctl status node > /dev/null 2>&1
  if [ $? -ne 0 ]; then
   service node status
   if [ $? -ne 0 ]; then
    systemctl start node > /dev/null 2>&1
    if [ $? -ne 0 ]; then
     service node start > /dev/null 2>&1
    fi
   fi
  fi
  systemctl status node > /dev/null 2>&1
  if [ $? -ne 0 ]; then
   service node status
   if [ $? -ne 0 ]; then
    echo "${ROUGE}Ne peut lancer node - Annulation${NORMAL}"
    exit 1
   fi
  fi
  echo "${CYAN}Enable node au démarrage${NORMAL}"
  systemctl enable node
 else
  echo "${ROUGE}Repertoire introuvable${NORMAL}"
 fi
 echo "${VERT}étape 6 nodejs réussie${NORMAL}"
}

#nettoyage
step_7_nettoyage() {
 echo "---------------------------------------------------------------------"
 echo "${JAUNE}Commence l'étape 7 nettoyage sources${NORMAL}"
 if [ -d ${REP_ROOT}/MeubleTV-${VERSION} ]; then
  rm -rf ${REP_ROOT}/MeubleTV-${VERSION}
 fi
 echo "${VERT}étape 7 nettoyage sources réussie${NORMAL}" 
}

#Variables
STEP=0
FASTLED_VERSION=3.3.2
VERSION=develop
HTML_OUTPUT=0
REP_ROOT=$PWD
while getopts ":s:v:h:" opt; do
  case $opt in
    s) STEP="$OPTARG"
    ;;
    v) VERSION="$OPTARG"
    ;;
	h) HTML_OUTPUT=1
	;;
    \?) echo "${ROUGE}Invalid option -$OPTARG${NORMAL}" >&2
    ;;
  esac
done

if [ ${HTML_OUTPUT} -eq 1 ]; then
  VERT="</pre><span style='color:green;font-weight: bold;'>"
  NORMAL="</span><pre>"
  ROUGE="<span style='color:red;font-weight: bold;'>"
  ROSE="<span style='color:pink;font-weight: bold;'>"
  BLEU="<span style='color:blue;font-weight: bold;'>"
  BLANC="<span style='color:white;font-weight: bold;'>"
  BLANCLAIR="<span style='color:blue;font-weight: bold;'>"
  JAUNE="<span style='color:#FFBF00;font-weight: bold;'>"
  CYAN="<span style='color:blue;font-weight: bold;'>"
  echo "<script>"
  echo "setTimeout(function(){ window.scrollTo(0,document.body.scrollHeight); }, 100);"
  echo "setTimeout(function(){ window.scrollTo(0,document.body.scrollHeight); }, 300);"
  echo "setTimeout(function(){ location.reload(); }, 1000);"
  echo "</script>"
  echo "<pre>"
fi

echo "${JAUNE}Bienvenue dans l'installateur de MeubleTV${NORMAL}"
echo "${JAUNE}Version d'installation de MeubleTV : ${VERSION}${NORMAL}"

case ${STEP} in
  0)
  echo "${JAUNE}Commence toutes les étapes de l'installation${NORMAL}"
	step_1_upgrade
	step_2_packages
	step_3_recupSources
	step_4_install_arduino
	step_5_install_nginx
	step_6_install_nodejs
	step_7_nettoyage
  echo "Installation finie. Un redémarrage devrait être effectué"
  ;;
  1)
  echo "${JAUNE}Commence toutes les étapes de l'installation des sources${NORMAL}"
	step_3_recupSources
	step_4_install_arduino
	step_5_install_nginx
	step_6_install_nodejs
	step_7_nettoyage
  echo "Installation finie."
  ;;
  2) 
  echo "${JAUNE}Commence toutes les étapes de l'installation des sources${NORMAL}"
	step_1_upgrade
	step_2_packages
  echo "Mise à jour des paquets terminée"
  ;;
  3) step_3_recupSources
  ;;
  4) step_4_install_arduino
  ;;
  5) step_5_install_nginx
  ;;
  6) step_6_install_nodejs
  ;;
  7) step_7_nettoyage
  ;;
  9) step_uninstall
  ;;
  *) echo "${ROUGE}Désolé, Je ne peux sélectionner une ${STEP} étape pour vous !${NORMAL}"
  ;;
esac

exit 0
