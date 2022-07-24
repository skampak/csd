/**************************************************//**
 * @file   myuniverse.h                              *
 * @author Foivos S. Zakkak <zakkak@csd.uoc.gr>       *
 *                                                    *
 * @brief  Header file with the structures and        *
 * function prototypes for the needs of the project   *
 ******************************************************/

#ifndef MYUNIVERSE_H_
#define MYUNIVERSE_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <assert.h>

#define N 100                   /**< Maximum number of galaxies in the
                                 * universe */
#define M  50                   /**< Maximum number of orphan clusters
                                 * per galaxy */

////////////////////////////////////////////////////////////////////////////////
//                  Declaring the needed structures
//                The definitions are in myuniverse.c
////////////////////////////////////////////////////////////////////////////////
typedef struct galaxy   galaxy_t;
typedef struct solar    solar_t;
typedef struct planet   planet_t;
typedef struct ocluster ocluster_t;

////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////
//                    Defining the needed structures
////////////////////////////////////////////////////////////////////////////////

/**
 * Structure defining a node of the planets list (lista planitwn)
 */
struct ocluster {
	int           cid;         /**< The orphan cluster identifier. >0 */
	planet_t     *orphans;     /**< Pointer to the first node in the
	                            * orphan planets list (lista orfanwn
	                            * planitwn) */
};

/**
 * Structure defining a node of the galaxies array (pinakas gala3iwn)
 */
struct galaxy {
	int         gid;       /**< The galaxy identifier. >0 */
	solar_t    *solars;    /**< Pointer to the first element in the
	                        * solar systems list (lista iliakwn
	                        * sistimatwn) */
	ocluster_t  oclusters[M];   /**< The orphan clusters array
	                             * (pinakas sistadwn orfanwn
	                             * planitwn) */
	solar_t    *ssentinel; /**< Pointer to the sentinel node (komvo
	                        * frouro) of the solar systems list (lista
	                        * iliakwn sistimatwn) */
};

/**
 * Structure defining a node of the solar systems list (lista iliakwn
 * sistimatwn)
 */
struct solar {
	int           sid;         /**< The solar system identifier. >0 */
	planet_t     *planets;     /**< Pointer to the first node in the
	                            * planets list (lista planitwn) */
	solar_t      *next;        /**< Pointer to the next node in the
	                            * solar systems list (lista iliakwn
	                            * sistimatwn) */
};

/**
 * Structure defining a node of the planets list (lista planitwn)
 */
struct planet {
	int           pid;         /**< The planet identifier. >0 */
	int           distance;    /**< The distance from the previous
	                            * planet in this planets list */
	planet_t     *previous;    /**< Pointer to the previous node in
	                            * the planets list (lista planitwn) */
	planet_t     *next;        /**< Pointer to the next node in the
	                            * planets list (lista planitwn) */
};

////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
//             Declaring the Galaxies array
////////////////////////////////////////////////////////////////////////////////
// For simplicity we declare the Galaxies array as a global variable
extern galaxy_t Galaxies[N];    /**< The galaxies array (pinakas
                                 * gala3iwn). This is an array of
                                 * lists */
extern int      Gindex;         /**< An index to the first free position in
	                             * the galaxies array, the use of this
	                             * field is optional */
////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////
//             Declaring the needed function prototypes
////////////////////////////////////////////////////////////////////////////////

/**
 * @brief Initializes the system.
 *
 * @return 1 on success
 *         0 on failure
 */
int big_bang();

/**
 * @brief Create a new galaxy and add it to the universe
 *
 * @param gid The new galaxy's id
 *
 * @return 1 on success
 *         0 on failure
 */
int galaxy_creation(int gid);

/**
 * @brief Create a new solar system and add it to the galaxy with id gid
 *
 * @param sid The new solar system's star id
 * @param gid The galaxy's id to add the new solar system
 *
 * @return 1 on success
 *         0 on failure
 */
int star_birth(int sid, int gid);

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
int planet_creation(int pid, int distance, int sid);

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
int star_death(int sid, int distance);

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
int planet_orphan_crash(int oid, int pid);

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
int orphans_cluster_crash(int cid1, int cid2, int cid3);

/**
 * @brief Merge two galaxies
 *
 * @param gid1 The first galaxy's id
 * @param gid2 The second galaxy's id
 *
 * @return 1 on success
 *         0 on failure
 */
int galaxy_merger(int gid1, int gid2);

/**
 * @brief Find a planet in the universe
 *
 * @param pid The planet's id
 *
 * @return 1 on success
 *         0 on failure
 */
int lookup_planet(int pid);

/**
 * @brief Find all planets in range distance from the planet with id pid
 *
 * @param pid      The planet's id
 * @param distance The search range
 *
 * @return 1 on success
 *         0 on failure
 */
int find_planets(int pid, int distance);

/**
 * @brief Print a solar system
 *
 * @param sid The solar system's id
 *
 * @return 1 on success
 *         0 on failure
 */
int print_solar(int sid);

/**
 * @brief Print an orphan planets cluster
 *
 * @param cid The orphan planets cluster's id
 *
 * @return 1 on success
 *         0 on failure
 */
int print_ocluster(int cid);

/**
 * @brief Print a galaxy
 *
 * @param gid The galaxy's id
 *
 * @return 1 on success
 *         0 on failure
 */
int print_galaxy(int gid);

/**
 * @brief Print the universe
 *
 * @return 1 on success
 *         0 on failure
 */
int print_universe();

/**
 * @brief Finalize the system, empty and free all the data structures
 *
 * @return 1 on success
 *         0 on failure
 */
int end_of_the_world();

////////////////////////////////////////////////////////////////////////////////

#endif /* MYUNIVERSE_H_ */
