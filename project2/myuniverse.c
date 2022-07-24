/**************************************************//**
 * @file   myuniverse.c                              *
 * @author Foivos S. Zakkak <zakkak@csd.uoc.gr>       *
 *                                                    *
 * @brief  Implementation of myuniverse.h            *
 ******************************************************/

#include "myuniverse.h"

// For simplicity we define the Galaxies array as a global variable
galaxy_t Galaxies[N];           /**< The galaxies array (pinakas
                                 * gala3iwn). This is an array of
                                 * lists */
int      Gindex;                /**< An index to the first free position in
                                 * the galaxies array, the use of this
                                 * field is optional */

////////////////////////////////////////////////////////////////////////////////
//                    Defining the needed functions
////////////////////////////////////////////////////////////////////////////////

/**
 * @brief Initializes the system.
 *
 * @return 1 on success
 *         0 on failure
 */
int big_bang() {
	
	int i;
	for(i=0;i<=N;i++) {
	
	Galaxies[i].gid=INT_MAX;
	Galaxies[i].solars=NULL;
	Galaxies[i].ssentinel=NULL;
	Galaxies[i].orphans->pid=INT_MAX;
	Galaxies[i].orphans->distance=INT_MAX;
	Galaxies[i].orphans->parent=NULL;
	Galaxies[i].orphans->rc=NULL;
	Galaxies[i].orphans->lc=NULL;
    }
    printf("B DONE\n");
    Gindex=0;
	
	return 1;
}

/**
 * @brief Create a new galaxy and add it to the universe
 *
 * @param gid The new galaxy's id
 *
 * @return 1 on success
 *         0 on failure
 */
int galaxy_creation(int gid) {
     int i=0;
     solar_t *ssentinel;
	ssentinel=(solar_t*)malloc(sizeof(solar_t));
	galaxy_t *gala;
	gala=(galaxy_t*)malloc(sizeof(galaxy_t));
	gala->gid=gid;
	gala->solars=gala->ssentinel;
	
	
	Galaxies[Gindex]=*gala;
	Gindex++;
printf("G %d\n", gid);
printf("Galaxies= ");
while(Galaxies[i].gid!=INT_MAX){
	printf("%d\n" ,Galaxies[i].gid);
	i++;
	return 1;
}
}
/**
 * @brief Create a new solar system and add it to the galaxy with id gid
 *
 * @param sid The new solar system's star id
 * @param gid The galaxy's id to add the new solar system
 *
 * @return 1 on success
 *         0 on failure
 */
int star_birth(int sid, int gid) {
	int j=0;
	 solar_t *star;
    planet_t *psentinel;
	while(Galaxies[j].gid!=INT_MAX){
	if(Galaxies[j].gid==gid)
	break;
	
	j++;
		
	}

    solar_t *solars ,*curr,*tail;
    
	star=(solar_t *)malloc(sizeof(solar_t));
	tail=(solar_t *)malloc(sizeof(solar_t));
	psentinel=(planet_t *)malloc(sizeof(planet_t));
	star->sid=sid;
	star->planets=star->psentinel;
	star->next=solars;
    tail->next=Galaxies[j].ssentinel;
	Galaxies[j].ssentinel=tail;
	solars=star;
	
	printf("Solars=\n");
	while(star!=NULL) {
		printf("%d",star->sid);
		star=star->next;
		
	}
	Galaxies[j].solars=star;
	
	
	
	
	return 1;
	
}

/**
 * @brief Create a new planet in the solar system with id sid
 *
 * @param pid      The new planet's id
 * @param distance The new planet's distance from the solar system's star
 * @param sid      The solar system's id to add the new planet
 *
 * @return 1 on success
 *         0 on failure
 */
int planet_creation(int pid, int distance, int sid) {
     int i;
	for(i=0;i<N;i++) {
		while(Galaxies[i].solars!=NULL)  {
		
		if(Galaxies[i].solars->sid=sid)
		break;
		Galaxies[i].solars=Galaxies[i].solars->next;	}
	}
	
	
	planet_t *temp,*prev;
	
	while(Galaxies[i].solars->planets!=NULL) {
	 if(Galaxies[i].solars->planets->pid==pid){
	 	Galaxies[i].solars->planets->distance=distance;
	 	Galaxies[i].solars->planets=Galaxies[i].solars->planets;
	 }
	 prev=Galaxies[i].solars->planets;
	 if(distance<Galaxies[i].solars->planets->distance)
	   Galaxies[i].solars->planets=Galaxies[i].solars->planets->lc;
	   else
	   Galaxies[i].solars->planets=Galaxies[i].solars->planets->rc;
}
temp=(planet_t *)malloc(sizeof(galaxy_t));
	temp->lc=NULL;
	temp->rc=NULL;
	temp->pid=pid;
	temp->distance=distance;
	if(prev==NULL) Galaxies[i].solars->planets=temp;
	else if(distance<prev->distance) prev->lc=temp;
	else prev->rc=temp;
	Galaxies[i].solars->planets=Galaxies[i].solars->planets;
	
	return 1;
}

/**
 * @brief Delete a solar system and delete all planets in range
 * distance from the solar system's star-sun. The remaining planets
 * form a new orphan planets cluster in the galaxy.
 *
 * @param sid      The solar system's id
 * @param distance The range in which to delete the planets
 *
 * @return 1 on success
 *         0 on failure
 */
int star_death(int sid, int distance) {
	return 1;
}

/**
 * @brief Delete the orphan planet with id oid and the planet with id
 * pid
 *
 * @param oid The orphan planet's id
 * @param pid The planet's id
 *
 * @return 1 on success
 *         0 on failure
 */
int planet_orphan_crash(int oid, int pid) {
	return 1;
}

/**
 * @brief Binary star creation
 *
 * @param sid1 The, to split, solar system
 * @param distance
 * @param sid2 The id of the first new solar system
 * @param sid3 The id of the second new solar system
 *
 * @return 1 on success
 *         0 on failure
 */
int binary_star_creation(int cid1, int distance, int cid2, int cid3) {
	return 1;
}

/**
 * @brief Find a planet in the universe
 *
 * @param pid The planet's id
 *

 * @return 1 on success
 *         0 on failure
 */
int lookup_planet(int pid) {
	int i=0;
   while(Galaxies[i].gid!=INT_MAX) {
   
	
      if(Galaxies[i].solars=NULL)
      return 0;
      i++;
  }
      while(Galaxies[i].solars!=NULL) {
	  Galaxies[i].solars->psentinel->pid=pid;
        while(pid!=Galaxies[i].solars->planets->pid) {
        	if(pid<Galaxies[i].solars->planets->pid) Galaxies[i].solars->planets=Galaxies[i].solars->planets->lc;
        	else
        	Galaxies[i].solars->planets=Galaxies[i].solars->planets->rc;
        	
		}
		if(Galaxies[i].solars->planets!=Galaxies[i].solars->psentinel) return 1;
		else return 0;
}
}

/**
 * @brief Find an orphan in the universe
 *
 * @param oid The orphan planet's id
 *
 * @return 1 on success
 *         0 on failure
 */
int lookup_orphan(int oid) {
	return 1;
}

/**
 * @brief Print a solar system
 *
 * @param sid The solar system's id
 *
 * @return 1 on success
 *         0 on failure
 */
 void InOrder(planet_t  *p){
 	if(p==NULL) return;
 	InOrder(p->lc);
 	printf("%d",p->pid);
 	InOrder(p->rc);
 }
int print_solar(int sid) {
	int j=0;
	while(Galaxies[j].gid!=INT_MAX)
	      if(Galaxies[j].solars==NULL) {
		  
	      return 0;
	  }
	  else
	   if(Galaxies[j].solars->sid==sid){
	   	InOrder(Galaxies[j].solars->planets);
	   	
	   }

	
	return 1;
}

/**
 * @brief Print the orphan planets of a galaxy
 *
 * @param gid The galaxy's id
 *
 * @return 1 on success
 *         0 on failure
 */
int print_orphans(int gid) {
	return 1;
}

/**
 * @brief Print a galaxy
 *
 * @param gid The galaxy's id
 *
 * @return 1 on success
 *         0 on failure
 */
int print_galaxy(int gid) {
	int k,s;
	for(k=0;k<N;k++) {
		if(Galaxies[k].gid==gid){
		
		if(Galaxies[k].solars==NULL) {
		
		return 0;}
		while(Galaxies[k].solars!=NULL)
		  Galaxies[k].solars->sid=s;
		  print_solar(s);
		
	}
		
	}
	return 1;
}

/**
 * @brief Print the universe
 *
 * @return 1 on success
 *         0 on failure
 */
int print_universe() {
		int i;
	for(i=0;i<=N;i++)
	  print_galaxy(Galaxies[i].gid);
	
	return 1;
}

/**
 * @brief Finalize the system, empty and free all the data structures
 *
 * @return 1 on success
 *         0 on failure
 */
int end_of_the_world() {
	return 1;
}

////////////////////////////////////////////////////////////////////////////////
