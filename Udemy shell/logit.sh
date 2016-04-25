#!/bin/bash


#logger -p user.info "My logger message with RANDOM number $VAR"

logit(){
	logger -i -s -t MSGTAG "randomly $1"
}

logit $RANDOM
logit $RANDOM
logit $RANDOM