#!/bin/bash

## Check voms
echo "@@@ Checking user certificate @@@"
USERKEY=~/.globus/userkey.pem
USERCERT=~/.globus/usercert.pem
if [ ! -f $USERKEY -o ! -f $USERCERT ]; then
  echo "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!"
  echo "!! Cannot find usercert.pem or userkey.pem !!"
  echo "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!"
  exit 2
fi

voms-proxy-info > /dev/null
if [ $? != 0 ]; then
  voms-proxy-init --rfc --voms cms
  voms-proxy-info > /dev/null
  if [ $? != 0 ]; then
    echo "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!"
    echo "!!VOMS proxy is not initialized!!"
    echo "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!"
    exit 2
  fi
fi
VOMS_PROXY=`voms-proxy-info -p`
X509_USER_PROXY=$VOMS_PROXY
