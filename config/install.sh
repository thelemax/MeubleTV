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

if [ $(id -u) != 0 ] ; then
  echo "Les droits de super-utilisateur (root) sont requis pour installer Jeedom"
  echo "Veuillez lancer 'sudo $0' ou connectez-vous en tant que root, puis relancez $0"
  exit 1
fi

apt_install() {
  apt-get -y install "$@"
  if [ $? -ne 0 ]; then
    echo "${ROUGE}Ne peut installer $@ - Annulation${NORMAL}"
    exit 1
  fi
}

step_1_upgrade() {
  echo "---------------------------------------------------------------------"
  echo "${JAUNE}Commence l'étape 1 de la révision${NORMAL}"
  
  apt-get update
  apt-get -f install
  apt-get -y dist-upgrade
  echo "${VERT}étape 1 de la révision réussie${NORMAL}"
}

step_2_mainpackage() {
  echo "---------------------------------------------------------------------"
  echo "${JAUNE}Commence l'étape 2 paquet principal${NORMAL}"
  apt_install ntp ca-certificates unzip curl sudo cron
  apt-get -y install locate tar telnet wget logrotate fail2ban dos2unix ntpdate htop iotop vim iftop smbclient
  apt-get -y install git nano
  echo "${VERT}étape 2 paquet principal réussie${NORMAL}"
}

step_3_nginx() {
  echo "---------------------------------------------------------------------"
  echo "${JAUNE}Commence l'étape 3 nginx${NORMAL}"
  apt_install nginx
  
 # echo "Check the status of nginx"
 # systemctl status nginx

  
  echo "Start nginx"
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

  echo "Enable nginx au démarrage"
  systemctl enable nginx
    
  echo "Paramètrage de nginx"
  #wget --no-check-certificate https://github.com/thelemax/MeubleTV/config/nginx/serveur.conf -O /tmp/nginx-serveur.conf
	  
  cp /tmp/nginx-serveur.conf /etc/nginx/sites-available/nginx-serveur.conf
  nginx -t
  #rm /tmp/nginx-serveur.conf
  /etc/init.d/nginx reload
  
  echo "${VERT}étape 3 nginx réussie${NORMAL}" 
}

step_4_nodejs() {
 echo "---------------------------------------------------------------------"
  echo "${JAUNE}Commence l'étape 4 nodejs${NORMAL}"
  
  #curl -sL https://deb.nodesource.com/setup_10.x | sudo -E bash -
  apt_install nodejs npm
  
  node -v
  npm -v

  npm install pm2
  echo "${VERT}étape 4 nodejs réussie${NORMAL}" 
}

step_5_arduino() {
 echo "---------------------------------------------------------------------"
  echo "${JAUNE}Commence l'étape 5 arduino${NORMAL}"
  apt-get_install arduino-core arduino-mk
  
  echo "Paramétrage des variables d'environnement arduino"
  export ARDUINO_DIR="/usr/share/arduino"
  export ARDMK_DIR="/usr/share/arduino"
  export AVR_TOOLS_DIR="/usr"
  export ISP_PORT="/dev/ttyACM0"
  
  echo "Copie des librairies arduino"
  #/usr/share/arduino/librairies
  #FastLED Wire SoftwareSerial
  #https://github.com/FastLED/FastLED/archive/master.zip
  #https://github.com/FastLED/FastLED/archive/3.3.2.zip

  cd /home/pi/git/MeubleTV/arduino-dev/
  make && sh upload.sh
}

step_6_meubletv() {
 echo "---------------------------------------------------------------------"
  echo "${JAUNE}Commence l'étape 6 meubletv${NORMAL}"

  
  mkdir /home/pi/git
  
  git clone https://github.com/thelemax/MeubleTV.git
  
  #https://github.com/thelemax/MeubleTV/archive/master.zip
  
  echo "Compilation et Téléversement du programme arduino"
  cd /home/pi/git/MeubleTV/arduino-dev/
  make
  sh upload.sh
  
  echo "Compilation et Démarrage du programme nodejs"
  cd /home/pi/git/MeubleTV/nodejs-dev/
  npm install
  node meuble-tv.js &
}

STEP=4
HTML_OUTPUT=0
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
  step_2_mainpackage
  step_3_nginx
  step_4_nodejs
  step_5_arduino
  step_6_meubletv
  echo "Installation finie. Un redémarrage devrait être effectué"
  ;;
  1) step_1_upgrade
  ;;
  2) step_2_mainpackage
  ;;
  3) step_3_nginx
  ;;
  4) step_4_nodejs
  ;;
  5) step_5_arduino
  ;;
  6) step_6_meubletv
  ;;
  *) echo "${ROUGE}Désolé, Je ne peux sélectionner une ${STEP} étape pour vous !${NORMAL}"
  ;;
esac

exit 0
