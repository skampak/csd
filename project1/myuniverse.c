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
	
	int s,i=0;
	
	galaxy_t *gala;
	gala=(galaxy_t*)malloc(sizeof(galaxy_t));
	gala->gid=gid;
	gala->solars=gala->ssentinel;
	
	///for(s=0;s<M;s++) {
	
	   //gala->oclusters[i].cid=INT_MAX;
	   //gala->oclusters[i].orphans=NULL;
//}
	Galaxies[Gindex]=*gala;
	Gindex++;
printf("G %d\n", gid);
printf("Galaxies= ");
while(Galaxies[i].gid!=INT_MAX){
	printf("%d\n" ,Galaxies[i].gid);
	i++;
}
	
	return 1;
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

	while(Galaxies[j].gid!=INT_MAX){
	if(Galaxies[j].gid==gid)
	break;
	
	j++;
		
	}

    solar_t *solars ,*curr,*tail;
    
	star=(solar_t *)malloc(sizeof(solar_t));
	star->sid=sid;
	star->planets=NULL;
	star->next=solars;
    //tail->next=Galaxies[j].ssentinel;
	//Galaxies[j].ssentinel=tail;
	solars=star;
	
	printf("Solars=\n");
	while(star!=NULL) {
		printf("%d",star->sid);
		star=star->next;
		
	}
	//Galaxies[j].solars=star;
	
	
	
	
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
	
	solar_t *solars;
	planet_t *planets;
	planet_t *temp;
	temp=(planet_t *)malloc(sizeof(galaxy_t));
	temp->previous=NULL;
	temp->next=NULL;
	temp->pid=pid;
	temp->distance=distance;
	if(Galaxies[i].solars->planets==NULL){
		Galaxies[i].solars->planets=temp;
		temp=Galaxies[i].solars->planets;
	}
	else{
		temp->next=Galaxies[i].solars->planets;
		Galaxies[i].solars->planets->previous=temp;
		Galaxies[i].solars->planets=temp;
	}
	

	
    
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
 * @brief Split an orphan planets cluster in two
 *
 * @param cid1 The, to split, orphan planets cluster's id
 * @param cid2 The orphan planets cluster's id for the first new cluster
 * @param cid3 The orphan planets cluster's id for the second new cluster
 *
 * @return 1 on success
 *         0 on failure
 */
int orphans_cluster_crash(int cid1, int cid2, int cid3) {
	return 1;
}

/**
 * @brief Merge two galaxies
 *
 * @param gid1 The first galaxy's id
 * @param gid2 The second galaxy's id
 *
 * @return 1 on success
 *         0 on failure
 */
int galaxy_merger(int gid1, int gid2) {
	
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
      while(Galaxies[i].solars!=NULL) {
	  
        if(Galaxies[i].solars->planets->pid==pid) {
         printf("%d", Galaxies[i].gid);
         printf("%d",Galaxies[i].solars->sid);
         printf("%d",Galaxies[i].solars->planets->pid);
		}
		else
		    Galaxies[i].solars=Galaxies[i].solars->next;
		}
		
	i++;
}
}
	

/**
 * @brief Find all planets in range distance from the planet with id pid
 *
 * @param pid      The planet's id
 * @param distance The search range
 *
 * @return 1 on success
 *         0 on failure
 */
int find_planets(int pid, int distance) {
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
int print_solar(int sid) {
	int j=0;
	while(Galaxies[j].gid!=INT_MAX)
	      if(Galaxies[j].solars==NULL) {
		  
	      return 0;
	  }
	  else
	   while(Galaxies[j].solars->planets->next != NULL) {
	   
	     printf("%d" , Galaxies[j].solars->planets->pid);
     Galaxies[j].solars->planets=Galaxies[j].solars->planets->next;
 }
 printf("%d", Galaxies[j].solars->planets->pid);

	return 1;
}

/**
 * @brief Print an orphan planets cluster
 *
 * @param cid The orphan planets cluster's id
 *
 * @return 1 on success
 *         0 on failure
 */
int print_ocluster(int cid) {
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
