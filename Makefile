#FICHIERS CORE DU JEU
CORE_VENDEUR = core/Vendeur/Vendeur.cpp core/Vendeur/Equipement.cpp
CORE_DECOR   = core/Decor/Decor.cpp core/Decor/Piece.cpp core/Decor/Mur.cpp core/Decor/Sol.cpp core/Decor/Sortie.cpp
CORE_PIEGE   = core/Piege/Piege.cpp
CORE         = core/Jeu.cpp core/Niveau.cpp core/Personnage.cpp $(CORE_VENDEUR) $(CORE_DECOR) $(CORE_PIEGE)

#FICHIERS DU JEU POUR VERSION TEXTE
SRC_TXT = $(CORE) txt/TXTjeu.cpp txt/TXTwin.cpp txt/main_txt.cpp
OUT_TXT = txt/student-struggle_txt

#FICHIERS DU JEU POUR VERSION SDL2
SRC_SDL = $(CORE) sdl2/SDLjeu.cpp sdl2/Image.cpp sdl2/Menu.cpp sdl2/Shop.cpp sdl2/Timer.cpp sdl2/main_sdl.cpp
OUT_SDL = sdl2/student-struggle_sdl

#FICHIERS DU JEU POUR LES TESTS DE REGRESSION
SRC_TEST = $(CORE) test/main_test.cpp
OUT_TEST = jeu_test



#INCLUDES ET LIBS DE LA SDL2
ifeq ($(OS),Windows_NT)
	INCLUDE_DIR_SDL = 	-Iextern/SDL2_mingw/SDL2/include \
						-Iextern/SDL2_mingw/SDL2_ttf/include/SDL2 \
						-Iextern/SDL2_mingw/SDL2_image/include/SDL2 \
						-Iextern/SDL2_mingw/SDL2_mixer/include/SDL2

	LIBS_SDL = -Lextern \
			-Lextern/SDL2_mingw/SDL2/lib \
			-Lextern/SDL2_mingw/SDL2_ttf/lib \
			-Lextern/SDL2_mingw/SDL2_image/lib \
			-Lextern/SDL2_mingw/SDL2_mixer/lib \
			-lmingw32 -lSDL2main -lSDL2.dll -lSDL2_ttf.dll -lSDL2_image.dll -lSDL2_mixer.dll

else
	INCLUDE_DIR_SDL = -I/usr/include/SDL2
	LIBS_SDL = -lSDL2 -lSDL2_ttf -lSDL2_image -lSDL2_mixer
endif



CC					    = g++
LD 					    = g++
LDFLAGS  			  =
CPPFLAGS 			  = -Wall -ggdb
OBJ_DIR 			  = obj
SRC_DIR 			  = src
BIN_DIR 			  = bin
INCLUDE_DIR		  = -Isrc -Isrc/core -Isrc/sdl2 -Isrc/txt



#make default
default: jeu_txt jeu_sdl clean

#make all
all: jeu_txt jeu_sdl jeu_test clean

#make jeu_txt
jeu_txt: mk_dir $(BIN_DIR)/$(OUT_TXT)

#make jeu_sdl
jeu_sdl: mk_dir $(BIN_DIR)/$(OUT_SDL)

#make jeu_test
jeu_test: mk_dir $(BIN_DIR)/$(OUT_TEST)



#CREATION DOSSIER OBJ ET BIN/TXT
mk_dir:
ifeq ($(OS),Windows_NT)
	if not exist $(OBJ_DIR) mkdir $(OBJ_DIR) $(OBJ_DIR)\txt $(OBJ_DIR)\sdl2 $(OBJ_DIR)\test $(OBJ_DIR)\core $(OBJ_DIR)\core\Vendeur $(OBJ_DIR)\core\Decor $(OBJ_DIR)\core\Piege
	if not exist $(BIN_DIR)\txt mkdir $(BIN_DIR)\txt
else
	test -d $(OBJ_DIR) || mkdir -p $(OBJ_DIR) $(OBJ_DIR)/txt $(OBJ_DIR)/sdl2 $(OBJ_DIR)/test $(OBJ_DIR)/core $(OBJ_DIR)/core/Vendeur $(OBJ_DIR)/core/Decor $(OBJ_DIR)/core/Piege
	test -d $(BIN_DIR)/txt || mkdir $(BIN_DIR)/txt
endif



#LINKAGE TEST REGRESSION
$(BIN_DIR)/$(OUT_TEST): $(SRC_TEST:%.cpp=$(OBJ_DIR)/%.o)
	$(LD) $+ -o $@ $(LDFLAGS)

#LINKAGE TXT
$(BIN_DIR)/$(OUT_TXT): $(SRC_TXT:%.cpp=$(OBJ_DIR)/%.o)
	$(LD) $+ -o $@ $(LDFLAGS)

#LINKAGE SDL
$(BIN_DIR)/$(OUT_SDL): $(SRC_SDL:%.cpp=$(OBJ_DIR)/%.o)
	$(LD) $+ -o $@ $(LDFLAGS) $(LIBS_SDL)


#COMPILATIONS FICHIERS SRC
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CC) -c $(CPPFLAGS) $(INCLUDE_DIR_SDL) $(INCLUDE_DIR) $< -o $@



#POUR EVITER UN CONFLIT AVEC UN FICHIER DU MEME NOM
.PHONY: clean veryclean doxygen

#make clean
clean:
ifeq ($(OS),Windows_NT)
	del /s /q $(OBJ_DIR)
else
	rm -rf $(OBJ_DIR)
endif

#make veryclean
veryclean: clean
ifeq ($(OS),Windows_NT)
	del /s /q $(BIN_DIR)\$(OUT_TXT)
	del /s /q $(BIN_DIR)\$(OUT_SDL)
	del /s /q $(BIN_DIR)\$(OUT_TEST)
else
	rm -f $(BIN_DIR)/$(OUT_TXT)
	rm -f $(BIN_DIR)/$(OUT_SDL)
	rm -f $(BIN_DIR)/$(OUT_TEST)
endif

#make doxygen
doxygen:
	doxygen doc/doxyfile.doxy
