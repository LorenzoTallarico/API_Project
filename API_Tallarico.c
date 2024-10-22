 //Tallarico Lorenzo
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAX_RICHIESTA 19

/**
 * @brief Represents a vehicle in the transportation system.
 *
 * This structure contains information about the vehicle's autonomy
 * and pointers to its left and right children in a binary tree.
 */
typedef struct Veicolo{
	long autonomia;		///< A long integer representing the vehicle's autonomy.
	struct Veicolo *dx;	///< Pointer to the right child vehicle node.
	struct Veicolo *sx;	///< Pointer to the left child vehicle node.
}Veicolo;

/**
 * @brief Represents a route in the transportation network.
 *
 * This structure contains a unique identifier for the route ('id') and a pointer
 * to the next route node in a linked list.
 */
typedef struct Route{
	long id;			///< A long integer representing the unique route ID.
	struct Route *next;	///< Pointer to the next route node in the linked list.
}Route;

/**
 * @brief Represents garbage collection data in the transportation system.
 *
 * This structure contains a pointer to a 'Route' and a pointer
 * to the next garbage node in a linked list.
 */
typedef struct Spazzatura{
	Route *route;				///< Pointer to the associated 'Route' structure.
	struct Spazzatura *next;	///< Pointer to the next garbage node in the linked list.
}Spazzatura;

/**
 * @brief Represents a station in the transportation network.
 *
 * This structure contains information about the station, including its unique
 * identifier, relationships with other stations, a binary tree of vehicles,
 * and routing information.
 */
typedef struct Stazione{
	long id;				///< long integer representing the unique station ID, indicating the distance in kilometers from the starting point of the road, starting from 0.
	Veicolo *root;			///< pointer to the root of a binary tree of 'Veicolo' structures.
	struct Stazione *dx;	///< pointer to the right child station node.
	struct Stazione *sx;	///< pointer to the left child station node.
	struct Stazione *padre;	///< pointer to the parent station node.
	Route *route;			///< pointer to a 'Route' structure.
	long maxAutonomia;		///< long integer representing the maximum vehicle range.
}Stazione;

/**
 * @brief Creates and initializes a 'Veicolo' structure.
 *
 * @param autonomia The autonomy value to be assigned to the vehicle.
 * @return A pointer to the newly created 'Veicolo' structure.
 */
Veicolo *creaVeicolo(long autonomia){
	Veicolo *v;
	v= (Veicolo *) malloc(sizeof(Veicolo));
	v->autonomia= autonomia;
	v->dx=NULL;
	v->sx=NULL;
	return (v);
}

/**
 * @brief Creates and initializes a 'Stazione' structure.
 *
 * @param id The unique identifier for the station.
 * @return A pointer to the newly created 'Stazione' structure.
 */
Stazione *creaStazione(long id){
	Stazione *s;
	s= (Stazione *) malloc(sizeof(Stazione));
	s->id=id;
	s->root=NULL;
	s->dx=NULL;
	s->sx=NULL;
	s->padre=NULL;
	s->maxAutonomia=0;
	s->route=NULL;
    return (s);
}

/**
 * @brief Searches for a station with a specific ID in a binary tree of stations.
 *
 * @param root Pointer to the root of the binary tree of 'Stazione'.
 * @param id The unique identifier of the station to search for.
 * @return A pointer to the 'Stazione' with the specified ID, or NULL if not found.
 */
Stazione *cercaStazione(Stazione *root, long id){
	if(root==NULL){
		return root;
	}
	else{
	while(root!=NULL){
		if(root->id==id){
			return root;
		}
		else if(root->id>id){
			if(root->sx!=NULL){
				root=root->sx;
			}
			else{
				return NULL;
			}
		}
		else{
			if(root->dx!=NULL){
				root=root->dx;
			}
			else{
				return NULL;
			}
		}
	  }
	}
	return NULL;
}

/**
 * @brief Inserts a vehicle into a binary tree of vehicles.
 *
 * @param root A pointer to the pointer of the root node of the binary tree of 'Veicolo'.
 * @param autonomia The autonomy value of the vehicle to be inserted.
 */
void inserisciVeicolo(Veicolo **root, long autonomia){
	if(*root==NULL){
			*root=creaVeicolo(autonomia);
		}
	else{
		if((*root)->autonomia >= autonomia){
			inserisciVeicolo(&((*root)->sx), autonomia);
		}
		else{
			inserisciVeicolo(&((*root)->dx), autonomia);
		}
	}
}

/**
 * @brief Inserts a station into a binary tree of stations in the appropriate position.
 *
 * @param root A pointer to the pointer of the root node of the binary tree of 'Stazione'.
 * @param id The unique identifier of the station to be inserted.
 * @param padre A pointer to the parent station of the new station being inserted.
 */
void inserisciStazione(Stazione **root, long id, Stazione *padre){
	if(*root==NULL){
			*root=creaStazione(id);
			(*root)->padre=padre;

		}
	else{
		if((*root)->id >= id){
			inserisciStazione(&((*root)->sx), id, *root);
		}
		else{
			inserisciStazione(&((*root)->dx), id, *root);
		}
	}
}

/**
 * @brief Removes a vehicle from a binary tree of vehicles based on its autonomy.
 *
 * @param root A pointer to the pointer of the root node of the binary tree of 'Veicolo'.
 * @param autonomia The autonomy value of the vehicle to be removed.
 * @return The autonomy of the removed vehicle, or -1 if the vehicle is not found.
 */
long eliminaVeicolo(Veicolo **root, long autonomia){
	Veicolo *v;
		v=*root;
		Veicolo *padreV=NULL;
		while(v!=NULL){
			if(v->autonomia<autonomia){
				padreV=v;
				v=v->dx;
			}
			else if(v->autonomia>autonomia){
				padreV=v;
				v=v->sx;
			}
			else{
				if(v->dx==NULL && v->sx==NULL){
					if(padreV!=NULL){
						if(padreV->autonomia<autonomia){
							padreV->dx=NULL;
						}
						else{
							padreV->sx=NULL;
						}
					}
					else{
						*root=NULL;
					}
					free(v);
					return autonomia;
				}
				else if(v->dx!=NULL && v->sx==NULL){
					if(padreV==NULL){
						*root=v->dx;
					}
					else{
						if(padreV->autonomia>autonomia){
							padreV->sx=v->dx;
						}
						else{
							padreV->dx=v->dx;
						}
					}
					free(v);
					return autonomia;
				}
				else if(v->dx==NULL && v->sx!=NULL){
					if(padreV==NULL){
						*root=v->sx;
					}
					else{
						if(padreV->autonomia>autonomia){
							padreV->sx=v->sx;
						}
						else{
							padreV->dx=v->sx;
						}
					}
					free(v);
					return autonomia;
				}
				else if(v->dx!=NULL && v->sx!=NULL){
					Veicolo *temp;
					temp=v->sx;
					if(temp->dx==NULL){
						v->autonomia=temp->autonomia;
						v->sx=temp->sx;
						free(temp);
					}
					else{
						while(temp->dx->dx!=NULL){
							temp=temp->dx;
						}
						v->autonomia=temp->dx->autonomia;
						eliminaVeicolo(&(temp->dx), temp->dx->autonomia);
					}
					return autonomia;
				}
			}
		}
		return -1;
	}

/**
 * @brief Deletes all vehicles in a binary tree of vehicles.
 *
 * @param root A pointer to the pointer of the root node of the binary tree of 'Veicolo'.
 */
void eliminaTuttiVeicoli(Veicolo **root){
	if(*root==NULL){
		return;
	}
	eliminaTuttiVeicoli(&((*root)->sx));
	eliminaTuttiVeicoli(&((*root)->dx));
	free(*root);
	*root=NULL;
}

/**
 * @brief Removes a station from a binary tree of stations based on its unique ID.
 *
 * @param root A pointer to the pointer of the root node of the binary tree of 'Stazione'.
 * @param id The unique identifier of the station to be removed.
 * @param elimina A flag indicating whether to delete all vehicles associated with the station (1)
 *                or not (0).
 * @return The unique ID of the removed station, or 0 if the station is not found.
 */
long eliminaStazione(Stazione **root, long id, long elimina){
	Stazione *s;
	s=(*root);
	Stazione *padreS=NULL;
	while(s!=NULL){
		if(s->id<id){
			padreS=s;
			s=s->dx;
		}
		else if(s->id>id){
			padreS=s;
			s=s->sx;
		}
		else{
			if(elimina==1){
				eliminaTuttiVeicoli(&(s->root));
			}

			s->root=NULL;
			if(s->dx==NULL && s->sx==NULL){
				if(padreS!=NULL){
					if(padreS->id<id){
						padreS->dx=NULL;
					}
					else{
						padreS->sx=NULL;
					}
				}
				else{
					(*root)=NULL;
				}
				free(s);
				return id;
			}
			else if(s->dx!=NULL && s->sx==NULL){
				if(padreS==NULL){
					(*root)=s->dx;
					s->dx->padre=NULL;
				}
				else{
					if(padreS->id>id){
						padreS->sx=s->dx;
						s->dx->padre=padreS;
					}
					else{
						s->dx->padre=padreS;
						padreS->dx=s->dx;
					}
				}
				free(s);
				return id;
			}
			else if(s->dx==NULL && s->sx!=NULL){
				if(padreS==NULL){
					(*root)=s->sx;
					s->sx->padre=NULL;
				}
				else{
					if(padreS->id>id){
						padreS->sx=s->sx;
						s->sx->padre=padreS;
					}
					else{
						s->sx->padre=padreS;
						padreS->dx=s->sx;
					}
				}
				free(s);
				return id;
			}
			else if(s->dx!=NULL && s->sx!=NULL){
				Stazione *temp;
				temp=s->sx;
				if(temp->dx==NULL){
					s->id=temp->id;
					s->sx=temp->sx;
					s->root=temp->root;
					s->maxAutonomia=temp->maxAutonomia;

					if(temp->sx!=NULL){
						temp->sx->padre=s;
					}
					free(temp);
				}
				else{
					while(temp->dx->dx!=NULL){
						temp=temp->dx;
					}
					s->id=temp->dx->id;
					s->root=temp->dx->root;
					s->maxAutonomia=temp->dx->maxAutonomia;
					eliminaStazione(&temp, temp->dx->id, 0);
				}
				return id;
			}
		}
	}
	return 0;
}

/**
 * @brief Recursively deletes all stations and their vehicles in the binary tree.
 *
 * @param root A pointer to the pointer of the root node of the binary tree of 'Stazione'.
 */
void ripulisciTutto(Stazione **root){
	if(*root==NULL){
			return;
		}
	ripulisciTutto(&((*root)->sx));
	ripulisciTutto(&((*root)->dx));
	eliminaTuttiVeicoli(&((*root)->root));
	free(*root);
	*root=NULL;
}

/**
 * @brief Recursively prints the autonomy of all vehicles in the binary tree (Post-order).
 *
 * @param root A pointer to the root node of the binary tree of 'Veicolo'.
 */
void stampaVeicoli(Veicolo *root){
	if (root != NULL) {
			stampaVeicoli(root->sx);
			stampaVeicoli(root->dx);
			printf("%li ", root->autonomia);
		}
}

/**
 * @brief Recursively prints the ID of each station and the autonomy of all its vehicles (Post-order).
 *
 * @param root A pointer to the root node of the binary tree of 'Stazione'.
 */
void stampaTutto(Stazione *root){
	if(root!=NULL){
		stampaTutto(root->sx);
		stampaTutto(root->dx);
		printf("id: %li; auto: ", root->id);
		stampaVeicoli(root->root);
		printf("\n");
	}
}

/**
 * @brief Finds the in-order successor of a station in the binary tree.
 *
 * @param curr A pointer to the current 'Stazione' node.
 * @return A pointer to the in-order successor, or NULL if none exists.
 */
Stazione *successiva(Stazione *curr){
	if(curr==NULL){
		return NULL;
	}
	if(curr->dx!=NULL){
		curr=curr->dx;
		while(curr->sx!=NULL){
			curr=curr->sx;
		}
		return curr;
	}
	else{
		Stazione *p=curr->padre;
		while(p!=NULL && curr==p->dx){
			curr=p;
			p=p->padre;
		}
		return p;
	}
}

/**
 * @brief Finds the in-order predecessor of a station in the binary tree.
 *
 * @param curr A pointer to the current 'Stazione' node.
 * @return A pointer to the in-order predecessor, or NULL if none exists.
 */
Stazione *precedente(Stazione *curr){
	if(curr==NULL){
		return NULL;
	}
	if(curr->sx!=NULL){
		curr=curr->sx;
		while(curr->dx!=NULL){
			curr=curr->dx;
		}
		return curr;
	}
	else{
		Stazione *p=curr->padre;
		while(p!=NULL && curr==p->sx){
			curr=p;
			p=p->padre;
		}
		return p;
	}

}

/**
 * @brief Creates a new route with the given ID.
 *
 * @param id The unique identifier for the route.
 * @return A pointer to the newly created 'Route' structure.
 */
Route *creaRoute( long id){
	Route *r= (Route *) malloc(sizeof(Route));
	r->id=id;
	r->next=NULL;
	return r;
}

/**
 * @brief Adds a new 'Spazzatura' node to the front of the list.
 *
 * @param lista A pointer to the head of the 'Spazzatura' linked list.
 * @param route A pointer to the 'Route' to be added.
 */
void aggiungiSpazzatura(Spazzatura **lista, Route *route){
	Spazzatura *s= (Spazzatura *) malloc(sizeof(Spazzatura));
	s->route=route;
	s->next=*lista;
	*lista=s;
}

/**
 * @brief Empties the 'Spazzatura' linked list.
 *
 * Frees all nodes and their associated 'Route'.
 *
 * @param lista A pointer to the head of the 'Spazzatura' linked list.
 */
void svuotaSpazzatura(Spazzatura **lista){
	Spazzatura *temp;
	while(*lista!=NULL){
		temp=*lista;
		*lista=(*lista)->next;
		free(temp->route);
		free(temp);
	}
}

/**
 * @brief Recursively prints the IDs of all routes in the list.
 *
 * @param lista A pointer to the head of the 'Route' linked list.
 */
void stampaRoute(Route *lista){
	if(lista==NULL){
		return;
	}
		stampaRoute(lista->next);
		printf("%li ", lista->id);
}

/**
 * @brief Creates a copy of the given 'Route' linked list.
 *
 * @param route A pointer to the head of the original 'Route' list.
 * @return A pointer to the head of the new copied 'Route' list.
 */
Route *salvaRoute(Route *route){
	if(route==NULL){
		return NULL;
	}
	Route *r=creaRoute(route->id);
	Route *rNext=r;
	route=route->next;
	while(route!=NULL){
		rNext->next=creaRoute(route->id);
		rNext=rNext->next;
		route=route->next;
	}
	return r;
}

/**
 * @brief Recursively searches for the best reachable station using binary tree properties.
 *
 * Marks the stations within ID limits, adds a route, and updates the last visited station.
 * @param maxPadre Pointer to the current station being inspected.
 * @param idPartenza Starting station ID.
 * @param minUltima Minimum ID of the last visited station.
 * @param maxId Maximum reachable station ID.
 * @param route Pointer to the current route.
 * @param ultimaVisitata Pointer to the last visited station.
 * @param listaSpazzatura Pointer to the garbage list for storing routes to be freed.
 */
void segnatoreSottoAlberoCrescente(Stazione *maxPadre, long idPartenza, long minUltima, long maxId, Route *route, Stazione **ultimaVisitata, Spazzatura **listaSpazzatura){
	if(maxPadre->sx!=NULL){
		if(maxPadre->id>minUltima){
			segnatoreSottoAlberoCrescente(maxPadre->sx, idPartenza, minUltima, maxId, route,ultimaVisitata, listaSpazzatura);
		}
	}
	if(maxPadre->dx!=NULL){
		if(maxPadre->id < maxId){
			segnatoreSottoAlberoCrescente(maxPadre->dx, idPartenza, minUltima, maxId, route, ultimaVisitata, listaSpazzatura);
		}
	}

	if((maxPadre->id<=maxId) && (maxPadre->id>idPartenza) && (maxPadre->route==NULL)){
		Route *r;
		r=creaRoute(idPartenza);
		aggiungiSpazzatura(listaSpazzatura, r);
		r->next=route;
		maxPadre->route=r;
		if(maxPadre->id>(*ultimaVisitata)->id){
			*ultimaVisitata=maxPadre;
		}

	}
	return;
}

/**
 * @brief Searches for the last parent station reachable based on given ID limits.
 *
 * @param maxPadre The current station from which the search begins.
 * @param idPartenza The starting station ID.
 * @param maxId The maximum allowed station ID for the search.
 * @return Returns the largest reachable station within the specified ID range.
 */
Stazione *cercaMaxPadre(Stazione *maxPadre, long idPartenza, long maxId){
	while(maxPadre->padre!=NULL){
		if((maxPadre->id < maxPadre->padre->id)&&(maxPadre->padre->id>maxId)){
			return maxPadre;
		}
		else{
			maxPadre=maxPadre->padre;
		}
	}
	return maxPadre;
}

/**
 * @brief Plans a route between ascending stations up to the arrival station.
 *
 * Uses a binary tree to search for stations with ascending IDs and update the route.
 *
 * @param startingStation The starting station.
 * @param arrivalId The ID of the arrival station.
 */
void pianificaPercorsoCrescente(Stazione *stazionePartenza, long idArrivo){
	Stazione *ultimaVisitata;
	ultimaVisitata=stazionePartenza;
	Stazione *maxPadre;
	Spazzatura *listaSpazzatura=NULL;
	long next=(successiva(ultimaVisitata))->id;
	while((stazionePartenza->id+stazionePartenza->maxAutonomia)<idArrivo){
		if(((stazionePartenza->id+stazionePartenza->maxAutonomia)>=next) && stazionePartenza->maxAutonomia>0){
			maxPadre=cercaMaxPadre(stazionePartenza, stazionePartenza->id, (stazionePartenza->id+stazionePartenza->maxAutonomia));
			segnatoreSottoAlberoCrescente(maxPadre, stazionePartenza->id, ultimaVisitata->id, stazionePartenza->id+stazionePartenza->maxAutonomia, stazionePartenza->route, &ultimaVisitata, &listaSpazzatura);
		}
		if(ultimaVisitata->id>=next){
		next=(successiva(ultimaVisitata))->id;
		}
		stazionePartenza->route=NULL;
		stazionePartenza=successiva(stazionePartenza);
		if(stazionePartenza==NULL){
			printf("nessun percorso\n");
			svuotaSpazzatura(&listaSpazzatura);
			return;
		}
		else if(stazionePartenza->route==NULL){
			printf("nessun percorso\n");
			svuotaSpazzatura(&listaSpazzatura);
			return;
		}
	}

	stampaRoute(stazionePartenza->route);
	printf("%li %li\n", stazionePartenza->id, idArrivo);
	svuotaSpazzatura(&listaSpazzatura);
	while(stazionePartenza->route!=NULL){
		stazionePartenza->route=NULL;
		stazionePartenza=successiva(stazionePartenza);
		if(stazionePartenza==NULL){
			return;
		}
	}
}

/**
 * @brief Recursively marks stations in a descending order binary tree and adds routes.
 *
 * @param minPadre The current station to inspect.
 * @param startId The starting station ID.
 * @param previousVisitedId The ID of the last visited station.
 * @param minId The minimum station ID to consider.
 * @param route The current route being constructed.
 * @param lastVisited A pointer to the last visited station.
 * @param trashList A pointer to the list of marked routes.
 */
void segnatoreSottoAlberoDecrescente(Stazione *minPadre, long idPartenza ,long ultimaVisitataPrecedente, long minId, Route *route, Stazione **ultimaVisitata, Spazzatura **listaSpazzatura){
	if(minPadre->sx!=NULL){
		if(minPadre->id>minId){
			segnatoreSottoAlberoDecrescente(minPadre->sx, idPartenza, ultimaVisitataPrecedente, minId, route,ultimaVisitata, listaSpazzatura);
		}
	}
	if(minPadre->dx!=NULL){
		if(minPadre->id < idPartenza){
			segnatoreSottoAlberoDecrescente(minPadre->dx, idPartenza, ultimaVisitataPrecedente, minId, route, ultimaVisitata, listaSpazzatura);
		}
	}
	if((minPadre->id>=minId) && (minPadre->id<ultimaVisitataPrecedente) && (minPadre->route==NULL)){
		Route *r;
		r=creaRoute(idPartenza);
		aggiungiSpazzatura(listaSpazzatura, r);
		r->next=route;
		minPadre->route=r;
		if(minPadre->id<(*ultimaVisitata)->id){
			*ultimaVisitata=minPadre;
		}
	}
	return;
}

/**
 * @brief Finds the minimum parent station reachable from the starting station.
 *
 * @param minPadre The current station to inspect.
 * @param startId The starting station ID.
 * @param minId The minimum station ID to consider.
 * @return Pointer to the minimum parent station, or NULL if not found.
 */
Stazione *cercaMinPadre(Stazione *minPadre, long idPartenza, long minId){
	while(minPadre->padre!=NULL){
		if((minPadre->id > minPadre->padre->id)&&(minPadre->padre->id<minId)){
			return minPadre;
		}
		else{
			minPadre=minPadre->padre;
		}
	}
	return minPadre;
}

/**
 * @brief Plans a descending route from the starting station to the destination.
 *
 * @param startStation The starting station for the route.
 * @param arrivalId The ID of the destination station.
 */
void pianificaPercorsoDecrescente(Stazione *stazionePartenza, long idArrivo){
	Stazione *ultimaVisitata;
	ultimaVisitata=stazionePartenza;
	Stazione *ultimaVisitataPrecedente;
	ultimaVisitataPrecedente=stazionePartenza;
	int passi=0;
	Stazione *minPadre;
	Spazzatura *listaSpazzatura=NULL;
	long limiteId=stazionePartenza->id;
	long next=(precedente(ultimaVisitata))->id;
	while((stazionePartenza->id-stazionePartenza->maxAutonomia)>idArrivo){
		if(((stazionePartenza->id-stazionePartenza->maxAutonomia)<=next) && stazionePartenza->maxAutonomia>0){
			minPadre=cercaMinPadre(stazionePartenza, stazionePartenza->id, (stazionePartenza->id-stazionePartenza->maxAutonomia));
			segnatoreSottoAlberoDecrescente(minPadre, stazionePartenza->id, ultimaVisitataPrecedente->id, (stazionePartenza->id-stazionePartenza->maxAutonomia), stazionePartenza->route, &ultimaVisitata, &listaSpazzatura);
			passi++;
		}
		if(ultimaVisitata->id<=next){
		next=(precedente(ultimaVisitata))->id;
		}
		if(ultimaVisitata->id==ultimaVisitataPrecedente->id && limiteId<=ultimaVisitata->id){
			printf("nessun percorso\n");
			stazionePartenza->route=NULL;
			svuotaSpazzatura(&listaSpazzatura);
			while(ultimaVisitata->route!=NULL){
				ultimaVisitata->route=NULL;
				ultimaVisitata=successiva(ultimaVisitata);
				if(ultimaVisitata==NULL){
					return;
				}
			}
			while(stazionePartenza->route!=NULL){
				stazionePartenza->route=NULL;
				stazionePartenza=successiva(stazionePartenza);
				if(stazionePartenza==NULL){
					return;
				}
				return;
			}
			return;
		}
		else if(stazionePartenza->id<limiteId){
			stazionePartenza->route=NULL;
			stazionePartenza=successiva(stazionePartenza);
		}
		else{
			stazionePartenza->route=NULL;
			stazionePartenza=ultimaVisitata;
			limiteId=precedente(ultimaVisitataPrecedente)->id;
			ultimaVisitataPrecedente=ultimaVisitata;
		}
	}
	stampaRoute(stazionePartenza->route);
	printf("%li %li\n", stazionePartenza->id, idArrivo);
	svuotaSpazzatura(&listaSpazzatura);
	while(ultimaVisitata->route!=NULL){
		ultimaVisitata->route=NULL;
		ultimaVisitata=successiva(ultimaVisitata);
		if(ultimaVisitata==NULL){
			return;
		}
	}
	while(stazionePartenza->route!=NULL){
		stazionePartenza->route=NULL;
		stazionePartenza=successiva(stazionePartenza);
		if(stazionePartenza==NULL){
			return;
		}
	}

}

/**
 * @brief Finds the maximum autonomy of vehicles in a binary tree.
 *
 * @param root The root of the vehicle tree.
 * @return The maximum autonomy value, or 0 if the tree is empty.
 */
long maxVeicolo(Veicolo *root){
	if(root==NULL){
		return 0;
	}
	else{
		while(root->dx!=NULL){
			root=root->dx;
		}
	}
	return root->autonomia;
}

/**
 * @brief Main function to manage the station and vehicle system.
 *
 * Reads commands from input, manages stations and vehicles, and plans routes.
 * Commands include adding/removing stations and vehicles, and planning routes.
 */
int main(){

	long numeroAuto, id, idArrivo;
	long autonomia;
	char richiesta[MAX_RICHIESTA];
	Stazione *rootStazioni=NULL;
	Stazione *tempStazione;
	rootStazioni=NULL;
	FILE *test=stdin; //fopen("open_1.txt", "r"); stdin;

	while(fscanf(test, "%s", richiesta)!=EOF){
		if(strcmp(richiesta,"aggiungi-stazione")==0){
			if(fscanf(test, "%li", &id)!=EOF){
				tempStazione=cercaStazione(rootStazioni, id);
				if(tempStazione==NULL){
					inserisciStazione(&rootStazioni, id, rootStazioni);
					if((fscanf(test, "%li", &numeroAuto))!=EOF){
						tempStazione=cercaStazione(rootStazioni, id);
						while(numeroAuto!=0){
							if((fscanf(test, "%li", &autonomia))!=EOF){
								inserisciVeicolo(&(tempStazione->root), autonomia);
								if(tempStazione->maxAutonomia<autonomia){
									tempStazione->maxAutonomia=autonomia;
								}
								numeroAuto--;
								}
						}
						printf("aggiunta\n");
					}
				}
				else{
					printf("non aggiunta\n");
				}
			}
		}
		else if(strcmp(richiesta,"demolisci-stazione")==0){
			if(fscanf(test, "%li", &id)!=EOF){
				tempStazione=cercaStazione(rootStazioni, id);
				if(tempStazione!=NULL){
					eliminaStazione(&rootStazioni, tempStazione->id, 1);
					printf("demolita\n");
				}
				else{
					printf("non demolita\n");
				}
			}
		}
		else if(strcmp(richiesta,"aggiungi-auto")==0){
			if(fscanf(test, "%li %li", &id, &autonomia)!=EOF){
				tempStazione=cercaStazione(rootStazioni, id);
				if((tempStazione)!=NULL){
					inserisciVeicolo(&(tempStazione->root), autonomia);
					if(tempStazione->maxAutonomia<autonomia){
						tempStazione->maxAutonomia=autonomia;
					}
					printf("aggiunta\n");
				}
				else{
					printf("non aggiunta\n");
				}
			}
		}
		else if(strcmp(richiesta,"rottama-auto")==0){
			if(fscanf(test, "%li %li", &id, &autonomia)!=EOF){
				if((tempStazione=cercaStazione(rootStazioni, id))!=NULL){
					if(eliminaVeicolo(&(tempStazione->root), autonomia)==autonomia){
						printf("rottamata\n");
						if(tempStazione->maxAutonomia==autonomia){
							tempStazione->maxAutonomia=maxVeicolo(tempStazione->root);
						}
					}
					else{
						printf("non rottamata\n");
					}
				}
				else{
					printf("non rottamata\n");
				}
			}
		}
		else if(strcmp(richiesta,"pianifica-percorso")==0){
			if(fscanf(test, "%li %li", &id, &idArrivo)!=EOF){
				tempStazione=cercaStazione(rootStazioni, id);
				if(id<idArrivo){
					pianificaPercorsoCrescente(tempStazione, idArrivo);
				}
				else{
					pianificaPercorsoDecrescente(tempStazione, idArrivo);
				}
			}
		}
	}
	ripulisciTutto(&rootStazioni);
	rootStazioni=NULL;
	fclose(test);
	return 0;
}

