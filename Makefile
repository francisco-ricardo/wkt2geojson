# ABSTRACT: Tasks
# make help
#

.PHONY: all run post_install push deploy help

CONTAINER ?= wkt2geojson

APP_ROOT_DIR := $(shell dirname $(realpath $(lastword $(MAKEFILE_LIST))))

# target: all - Executa o container de producao
all: run

# target: run_dev - Executa o container, type=dev, image=wkt2geojson:latest, mem=20, name=wkt2geojson
run:
	exec $(APP_ROOT_DIR)/scripts/host/run_container.sh -t dev -m 20 -i wkt2geojson:latest -n wkt2geojson
	docker exec -u 0 $(CONTAINER) $(APP_ROOT_DIR)/scripts/container/install_dev_packages.sh	


# target: post_install - Executa os scripts pos criacao da imagem
post_install:
	docker exec -u 0 $(CONTAINER) $(APP_ROOT_DIR)/scripts/container/set_timezone.sh


# target: deploy - Copia o conteudo relevante do diretorio APP_ROOT_DIR para um host remoto
deploy: guard-user guard-host
	$(APP_ROOT_DIR)/scripts/host/deploy_app.sh -u $(user) -h $(host)


# target: chown - Ajusta o owner dos arquivos para $USER
chown:
	sudo chown -R 1000:1000 $(APP_ROOT_DIR)


# target: push - Push para os repositorios remotos do Git
push:
	git push origin $(branch)


# Aborta se a variavel especificada nao estiver definida
guard-%:
	@ if [ "${${*}}" = "" ]; then \
		echo "Variavel $* indefinida"; \
		exit 1; \
	fi


# target: help - Mostra os targets que sao executaveis
help:
	@egrep "^# target:" [Mm]akefile

# EOF

