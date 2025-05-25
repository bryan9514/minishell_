/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_codes.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-mens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 12:23:37 by yel-mens          #+#    #+#             */
/*   Updated: 2025/05/02 12:25:05 by yel-mens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXIT_CODES_H
# define EXIT_CODES_H

// Standard exit codes
# define EXIT_SUCCESS         0     // Succès
# define EXIT_FAILURE         1     // Échec générique
# define EXIT_SYNTAX_ERROR    2     // Erreur de syntaxe

// Command-related exit codes (POSIX-compatible)
# define EXIT_CANNOT_EXECUTE 126   // Commande non exécutable (permissions)
# define EXIT_CMD_NOT_FOUND  127   // Commande introuvable
# define EXIT_SIGINT         130   // Ctrl+C
# define EXIT_SIGQUIT        131   // Ctrl+'\'
# define EXIT_SEGFAULT       139   // Segfault (pour debug)
# define EXIT_FATAL          255   // Erreur fatale / valeur hors plage

// Custom internal shell errors
# define EXIT_MALLOC         42    // Erreur d'allocation mémoire
# define EXIT_ENV            43    // Erreur liée aux variables d'environnement
# define EXIT_FD             44    // Erreur de descripteur de fichier
# define EXIT_BUILTIN_ERROR  45    // Erreur dans l'exécution d'un builtin

#endif
