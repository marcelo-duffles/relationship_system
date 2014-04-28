#=============================================================================#
# Universidade Federal do Rio de Janeiro
# Escola Politécnica
# Departamento de Eletrônica e de Computação
# Professor Marcelo Luiz Drumond Lanza
# Computation II - Class 2004/2
# Authors: Carlo Fragni and Marcelo Duffles Donato Moreira
# Description: Project's Makefile
# Date: 22/10/2004
#=============================================================================#





#=============================================================================#
#============================== RCS's COMMENTS ===============================#
#=============================================================================#
# $Date: 2005/02/16 22:11:21 $ 	
# $Log: Makefile.ConectivaLinux,v $
# Revision 1.1  2005/02/16 22:11:21  marceloddm
# Initial revision
#
# Revision 1.10  2004/12/20 23:45:56  marceloddm
# Some alterations in login.cgi'MAKROS have been done
#
# Revision 1.9  2004/12/20 12:54:54  marceloddm
# getUsers() function dependencies have been adde
#
# Revision 1.8  2004/12/16 00:06:23  marceloddm
# login.cgi added
#
# Revision 1.7  2004/12/14 02:50:02  marceloddm
# Grammar corrections have been madeGrammar corrections have been made
#
# Revision 1.6  2004/12/13 07:32:21  marceloddm
# Language settings have been added
# Layout have been modified
# Tests programs have been removed
# Makros like BINARIES_DIR and CGIS_DIR have been added
# 
# Revision 1.4  2004/12/11 11:53:22  marceloddm 
# Author changed for 'marceloddm'
#=============================================================================#
#=============================================================================#
#=============================================================================#



#=============================================================================#
#=============================== INSTRUCTIONS ================================#
#=============================================================================#

#=============================================================================#
#=========================== Set your language here ==========================#
#===========================  Altere o Idioma aqui  ==========================#
#=============================================================================#
CFLAGS = -DENGLISH    -D_XOPEN_SOURCE -D__ML_CGI_GLOBAL_VARIABLES__ -Wall -g -c  #English
#CFLAGS  = -DPORTUGUESE -D_XOPEN_SOURCE -D__ML_CGI_GLOBAL_VARIABLES__ -Wall -g -c  #Portuguese
#=============================================================================#

#=============================================================================#
#============  Set the directory where the CGI will be saved       ===========#
#============  Altere o diretorio onde serão armazenadas as CGI's  ===========#
#=============================================================================#
CGIS_DIR = /home/zeus4/marceloddm/public/html/computacao_ii/pf/cgi
#=============================================================================#

#=============================================================================#
#============  Set the directory where the executable will be saved      =====#
#============  Altere o diretorio onde serão armazenados os executáveis  =====#
#=============================================================================#
BINARIES_DIR = /home/zeus4/marceloddm/private/computacao_ii/pf/binaries
#=============================================================================#


#=============================================================================#
#=============================================================================#
#=============================================================================#
#============  You do not need to change more anything on this file  =========#
#============  Voce não precisa alterar mais nada neste arquivo      =========#
#=============================================================================#
#=============================================================================#
#=============================================================================#


































#=============================================================================#
#================================ COMPILER ===================================#
#=============================================================================#
CC = gcc
#=============================================================================#
#=============================== LINK-EDITOR =================================#
#=============================================================================#
LD = gcc 
#=============================================================================#
#=========================== LINK-EDITOR's FLAGS =============================#
#=============================================================================#
LFLAGS = -Wall -g -o
#=============================================================================#
#=============================================================================#



#=============================================================================#
#============================== OBJECT CODES =================================#
#=============================================================================#
RELATIONSHIP_SYSTEM_OBJS = error.o functions.o help.o mountFamilyTree.o install.o editUserData.o getUsers.o acceptFriendshipInvitation.o addUser.o rejectFriendshipInvitation.o inviteFriend.o excludeFriend.o recoveryPassword.o changePassword.o getFriends.o ncursesMenu.o addParentRelationship.o editParentRelationship.o changeUserCategory.o getFriendshipInvitation.o inviteUser.o removeParentRelationship.o removeUser.o relationshipSystem.o
LOGIN_CGI_OBJS                                   = login.o error.o help.o functions.o
LOGOUT_CGI_OBJS                                  = logout.o error.o help.o functions.o
SHOW_ADD_USER_FORM_CGI_OBJS                      = showAddUserForm.o error.o help.o functions.o
SHOW_EDIT_USER_DATA_FORM_CGI_OBJS                = showEditUserDataForm.o error.o help.o functions.o
SHOW_REMOVE_USER_FORM_CGI_OBJS                   = showRemoveUserForm.o error.o help.o functions.o
SHOW_INVITE_USER_FORM_CGI_OBJS                   = showInviteUserForm.o error.o help.o functions.o
SHOW_INVITE_FRIEND_FORM_CGI_OBJS                 = showInviteFriendForm.o error.o help.o functions.o
SHOW_GET_FRIENDSHIP_INVITATION_FORM_CGI_OBJS     = showGetFriendshipInvitationForm.o error.o help.o functions.o
SHOW_ACCEPT_FRIENDSHIP_INVITATION_FORM_CGI_OBJS  = showAcceptFriendshipInvitationForm.o error.o help.o functions.o
SHOW_REJECT_FRIENDSHIP_INVITATION_FORM_CGI_OBJS  = showRejectFriendshipInvitationForm.o error.o help.o functions.o
SHOW_EXCLUDE_FRIEND_FORM_CGI_OBJS                = showExcludeFriendForm.o error.o help.o functions.o
SHOW_GET_FRIENDS_FORM_CGI_OBJS                   = showGetFriendsForm.o error.o help.o functions.o
SHOW_CHANGE_USER_CATEGORY_FORM_CGI_OBJS          = showChangeUserCategoryForm.o error.o help.o functions.o
SHOW_ADD_PARENT_RELATIONSHIP_FORM_CGI_OBJS       = showAddParentRelationshipForm.o error.o help.o functions.o
SHOW_REMOVE_PARENT_RELATIONSHIP_FORM_CGI_OBJS    = showRemoveParentRelationshipForm.o error.o help.o functions.o
SHOW_EDIT_PARENT_RELATIONSHIP_FORM_CGI_OBJS      = showEditParentRelationshipForm.o error.o help.o functions.o
SHOW_GET_USERS_FORM_CGI_OBJS                     = showGetUsersForm.o error.o help.o functions.o
SHOW_RECOVERY_PASSWORD_FORM_CGI_OBJS             = showRecoveryPasswordForm.o error.o help.o functions.o
SHOW_RECOVERY_USER_PASSWORD_FORM_CGI_OBJS        = showRecoveryUserPasswordForm.o error.o help.o functions.o
SHOW_CHANGE_PASSWORD_FORM_CGI_OBJS               = showChangePasswordForm.o error.o help.o functions.o
SHOW_NEW_USER_FORM_CGI_OBJS                      = showNewUserForm.o error.o help.o functions.o
SHOW_NEW_USER_LOGIN_FORM_CGI_OBJS                = showNewUserLoginForm.o error.o help.o functions.o
SHOW_MENU_CGI_OBJS                               = showMenu.o error.o help.o functions.o
SHOW_WELCOME_PAGE_CGI_OBJS                       = showWelcomePage.o error.o help.o functions.o
SHOW_MOUNT_FAMILY_TREE_FORM_CGI_OBJS             = showMountFamilyTreeForm.o error.o help.o functions.o
ADD_USER_CGI_OBJS                                = cgiAddUser.o addUser.o error.o help.o functions.o
NEW_USER_CGI_OBJS                                = cgiNewUser.o addUser.o error.o help.o functions.o
EDIT_USER_DATA_CGI_OBJS                          = cgiEditUserData.o editUserData.o error.o help.o functions.o
REMOVE_USER_CGI_OBJS                             = cgiRemoveUser.o removeUser.o error.o help.o functions.o
INVITE_USER_CGI_OBJS                             = cgiInviteUser.o inviteUser.o error.o help.o functions.o
INVITE_FRIEND_CGI_OBJS                           = cgiInviteFriend.o inviteFriend.o error.o help.o functions.o
GET_FRIENDSHIP_INVITATION_CGI_OBJS               = cgiGetFriendshipInvitation.o getFriendshipInvitation.o error.o help.o functions.o
ACCEPT_FRIENDSHIP_INVITATION_CGI_OBJS            = cgiAcceptFriendshipInvitation.o acceptFriendshipInvitation.o error.o help.o functions.o
REJECT_FRIENDSHIP_INVITATION_CGI_OBJS            = cgiRejectFriendshipInvitation.o rejectFriendshipInvitation.o error.o help.o functions.o
EXCLUDE_FRIEND_CGI_OBJS                          = cgiExcludeFriend.o excludeFriend.o error.o help.o functions.o
GET_FRIENDS_CGI_OBJS                             = cgiGetFriends.o getFriends.o error.o help.o functions.o
CHANGE_USER_CATEGORY_CGI_OBJS                    = cgiChangeUserCategory.o changeUserCategory.o editUserData.o error.o help.o functions.o
ADD_PARENT_RELATIONSHIP_CGI_OBJS                 = cgiAddParentRelationship.o addParentRelationship.o error.o help.o functions.o
REMOVE_PARENT_RELATIONSHIP_CGI_OBJS              = cgiRemoveParentRelationship.o removeParentRelationship.o error.o help.o functions.o
EDIT_PARENT_RELATIONSHIP_CGI_OBJS                = cgiEditParentRelationship.o editParentRelationship.o error.o help.o functions.o
GET_USERS_CGI_OBJS                               = cgiGetUsers.o getUsers.o error.o help.o functions.o
RECOVERY_PASSWORD_CGI_OBJS                       = cgiRecoveryPassword.o recoveryPassword.o error.o help.o functions.o
RECOVERY_USER_PASSWORD_CGI_OBJS                  = cgiRecoveryUserPassword.o recoveryPassword.o error.o help.o functions.o
CHANGE_PASSWORD_CGI_OBJS                         = cgiChangePassword.o changePassword.o error.o help.o functions.o
MOUNT_FAMILY_TREE_CGI_OBJS                       = cgiMountFamilyTree.o mountFamilyTree.o error.o help.o functions.o
#=============================================================================#
#=============================================================================#



#=============================================================================#
#============================ EXECUTABLE FILES ===============================#
#=============================================================================#
EXECS = relationshipSystem login.cgi logout.cgi showAddUserForm.cgi showEditUserDataForm.cgi showRemoveUserForm.cgi showInviteUserForm.cgi showInviteFriendForm.cgi showGetFriendshipInvitationForm.cgi showAcceptFriendshipInvitationForm.cgi showRejectFriendshipInvitationForm.cgi showExcludeFriendForm.cgi showGetFriendsForm.cgi showChangeUserCategoryForm.cgi showAddParentRelationshipForm.cgi showRemoveParentRelationshipForm.cgi showEditParentRelationshipForm.cgi showGetUsersForm.cgi showRecoveryPasswordForm.cgi showRecoveryUserPasswordForm.cgi showChangePasswordForm.cgi showNewUserForm.cgi showNewUserLoginForm.cgi showMenu.cgi showWelcomePage.cgi showMountFamilyTreeForm.cgi addUser.cgi editUserData.cgi removeUser.cgi inviteUser.cgi inviteFriend.cgi getFriendshipInvitation.cgi acceptFriendshipInvitation.cgi rejectFriendshipInvitation.cgi excludeFriend.cgi getFriends.cgi changeUserCategory.cgi addParentRelationship.cgi removeParentRelationship.cgi editParentRelationship.cgi getUsers.cgi recoveryPassword.cgi recoveryUserPassword.cgi changePassword.cgi newUser.cgi mountFamilyTree.cgi
#=============================================================================#
#=============================================================================#



#=============================================================================#
#============================== IMPLICIT RULE ================================#
#=============================================================================#
.c.o:
	$(CC) $(CFLAGS) $<
#=============================================================================#
#=============================================================================#



#=============================================================================#
#================================= LABELS ====================================#
#=============================================================================#
all: $(EXECS)

relationshipSystem:			$(RELATIONSHIP_SYSTEM_OBJS)
	$(LD) $(LFLAGS) $@ $(RELATIONSHIP_SYSTEM_OBJS) -lcrypt -lmenu -lform -lncurses -L. -lsendmail -lgnugetopt 
	mv $@ $(BINARIES_DIR)

login.cgi:				$(LOGIN_CGI_OBJS)
	$(LD) $(LFLAGS) $@ $(LOGIN_CGI_OBJS) -lcrypt -lmenu -lform -lncurses -L. -lmlcgi
	mv $@ $(CGIS_DIR)/$@
	
logout.cgi:				$(LOGOUT_CGI_OBJS)
	$(LD) $(LFLAGS) $@ $(LOGOUT_CGI_OBJS) -lcrypt -lmenu -lform -lncurses -L. -lmlcgi
	mv $@ $(CGIS_DIR)/$@
	
showAddUserForm.cgi:			$(SHOW_ADD_USER_FORM_CGI_OBJS)
	$(LD) $(LFLAGS) $@ $(SHOW_ADD_USER_FORM_CGI_OBJS) -lcrypt -lmenu -lform -lncurses -L. -lmlcgi
	mv $@ $(CGIS_DIR)/$@
	
showEditUserDataForm.cgi:		$(SHOW_EDIT_USER_DATA_FORM_CGI_OBJS)
	$(LD) $(LFLAGS) $@ $(SHOW_EDIT_USER_DATA_FORM_CGI_OBJS) -lcrypt -lmenu -lform -lncurses -L. -lmlcgi
	mv $@ $(CGIS_DIR)/$@
	
showRemoveUserForm.cgi:			$(SHOW_REMOVE_USER_FORM_CGI_OBJS)
	$(LD) $(LFLAGS) $@ $(SHOW_REMOVE_USER_FORM_CGI_OBJS) -lcrypt -lmenu -lform -lncurses -L. -lmlcgi
	mv $@ $(CGIS_DIR)/$@
	
showInviteUserForm.cgi:			$(SHOW_INVITE_USER_FORM_CGI_OBJS)
	$(LD) $(LFLAGS) $@ $(SHOW_INVITE_USER_FORM_CGI_OBJS) -lcrypt -lmenu -lform -lncurses -L. -lmlcgi
	mv $@ $(CGIS_DIR)/$@
	
showInviteFriendForm.cgi:		$(SHOW_INVITE_FRIEND_FORM_CGI_OBJS)
	$(LD) $(LFLAGS) $@ $(SHOW_INVITE_FRIEND_FORM_CGI_OBJS) -lcrypt -lmenu -lform -lncurses -L. -lmlcgi
	mv $@ $(CGIS_DIR)/$@
	
showGetFriendshipInvitationForm.cgi:	$(SHOW_GET_FRIENDSHIP_INVITATION_FORM_CGI_OBJS)
	$(LD) $(LFLAGS) $@ $(SHOW_GET_FRIENDSHIP_INVITATION_FORM_CGI_OBJS) -lcrypt -lmenu -lform -lncurses -L. -lmlcgi
	mv $@ $(CGIS_DIR)/$@
	
showAcceptFriendshipInvitationForm.cgi:	$(SHOW_ACCEPT_FRIENDSHIP_INVITATION_FORM_CGI_OBJS)
	$(LD) $(LFLAGS) $@ $(SHOW_ACCEPT_FRIENDSHIP_INVITATION_FORM_CGI_OBJS) -lcrypt -lmenu -lform -lncurses -L. -lmlcgi
	mv $@ $(CGIS_DIR)/$@
	
showRejectFriendshipInvitationForm.cgi:	$(SHOW_REJECT_FRIENDSHIP_INVITATION_FORM_CGI_OBJS)
	$(LD) $(LFLAGS) $@ $(SHOW_REJECT_FRIENDSHIP_INVITATION_FORM_CGI_OBJS) -lcrypt -lmenu -lform -lncurses -L. -lmlcgi
	mv $@ $(CGIS_DIR)/$@
	
showExcludeFriendForm.cgi:		$(SHOW_EXCLUDE_FRIEND_FORM_CGI_OBJS)
	$(LD) $(LFLAGS) $@ $(SHOW_EXCLUDE_FRIEND_FORM_CGI_OBJS) -lcrypt -lmenu -lform -lncurses -L. -lmlcgi
	mv $@ $(CGIS_DIR)/$@
	
showGetFriendsForm.cgi:			$(SHOW_GET_FRIENDS_FORM_CGI_OBJS)
	$(LD) $(LFLAGS) $@ $(SHOW_GET_FRIENDS_FORM_CGI_OBJS) -lcrypt -lmenu -lform -lncurses -L. -lmlcgi
	mv $@ $(CGIS_DIR)/$@
	
showChangeUserCategoryForm.cgi:		$(SHOW_CHANGE_USER_CATEGORY_FORM_CGI_OBJS)
	$(LD) $(LFLAGS) $@ $(SHOW_CHANGE_USER_CATEGORY_FORM_CGI_OBJS) -lcrypt -lmenu -lform -lncurses -L. -lmlcgi
	mv $@ $(CGIS_DIR)/$@
	
showAddParentRelationshipForm.cgi:	$(SHOW_ADD_PARENT_RELATIONSHIP_FORM_CGI_OBJS)
	$(LD) $(LFLAGS) $@ $(SHOW_ADD_PARENT_RELATIONSHIP_FORM_CGI_OBJS) -lcrypt -lmenu -lform -lncurses -L. -lmlcgi
	mv $@ $(CGIS_DIR)/$@
	
showRemoveParentRelationshipForm.cgi:	$(SHOW_REMOVE_PARENT_RELATIONSHIP_FORM_CGI_OBJS)
	$(LD) $(LFLAGS) $@ $(SHOW_REMOVE_PARENT_RELATIONSHIP_FORM_CGI_OBJS) -lcrypt -lmenu -lform -lncurses -L. -lmlcgi
	mv $@ $(CGIS_DIR)/$@
	
showEditParentRelationshipForm.cgi:	$(SHOW_EDIT_PARENT_RELATIONSHIP_FORM_CGI_OBJS)
	$(LD) $(LFLAGS) $@ $(SHOW_EDIT_PARENT_RELATIONSHIP_FORM_CGI_OBJS) -lcrypt -lmenu -lform -lncurses -L. -lmlcgi
	mv $@ $(CGIS_DIR)/$@
	
showGetUsersForm.cgi:			$(SHOW_GET_USERS_FORM_CGI_OBJS)
	$(LD) $(LFLAGS) $@ $(SHOW_GET_USERS_FORM_CGI_OBJS) -lcrypt -lmenu -lform -lncurses -L. -lmlcgi
	mv $@ $(CGIS_DIR)/$@
	
showRecoveryPasswordForm.cgi:		$(SHOW_RECOVERY_PASSWORD_FORM_CGI_OBJS)
	$(LD) $(LFLAGS) $@ $(SHOW_RECOVERY_PASSWORD_FORM_CGI_OBJS) -lcrypt -lmenu -lform -lncurses -L. -lmlcgi
	mv $@ $(CGIS_DIR)/$@
	
showRecoveryUserPasswordForm.cgi:	$(SHOW_RECOVERY_USER_PASSWORD_FORM_CGI_OBJS)
	$(LD) $(LFLAGS) $@ $(SHOW_RECOVERY_USER_PASSWORD_FORM_CGI_OBJS) -lcrypt -lmenu -lform -lncurses -L. -lmlcgi
	mv $@ $(CGIS_DIR)/$@
	
showChangePasswordForm.cgi:		$(SHOW_CHANGE_PASSWORD_FORM_CGI_OBJS)
	$(LD) $(LFLAGS) $@ $(SHOW_CHANGE_PASSWORD_FORM_CGI_OBJS) -lcrypt -lmenu -lform -lncurses -L. -lmlcgi
	mv $@ $(CGIS_DIR)/$@
	
showNewUserForm.cgi:			$(SHOW_NEW_USER_FORM_CGI_OBJS)
	$(LD) $(LFLAGS) $@ $(SHOW_NEW_USER_FORM_CGI_OBJS) -lcrypt -lmenu -lform -lncurses -L. -lmlcgi
	mv $@ $(CGIS_DIR)/$@
	
showNewUserLoginForm.cgi:		$(SHOW_NEW_USER_LOGIN_FORM_CGI_OBJS)
	$(LD) $(LFLAGS) $@ $(SHOW_NEW_USER_LOGIN_FORM_CGI_OBJS) -lcrypt -lmenu -lform -lncurses -L. -lmlcgi
	mv $@ $(CGIS_DIR)/$@
	
showMenu.cgi:				$(SHOW_MENU_CGI_OBJS)
	$(LD) $(LFLAGS) $@ $(SHOW_MENU_CGI_OBJS) -lcrypt -lmenu -lform -lncurses -L. -lmlcgi
	mv $@ $(CGIS_DIR)/$@
	
showWelcomePage.cgi:			$(SHOW_WELCOME_PAGE_CGI_OBJS)
	$(LD) $(LFLAGS) $@ $(SHOW_WELCOME_PAGE_CGI_OBJS) -lcrypt -lmenu -lform -lncurses -L. -lmlcgi
	mv $@ $(CGIS_DIR)/$@
	
showMountFamilyTreeForm.cgi:		$(SHOW_MOUNT_FAMILY_TREE_FORM_CGI_OBJS)
	$(LD) $(LFLAGS) $@ $(SHOW_MOUNT_FAMILY_TREE_FORM_CGI_OBJS) -lcrypt -lmenu -lform -lncurses -L. -lmlcgi
	mv $@ $(CGIS_DIR)/$@
	
addUser.cgi:				$(ADD_USER_CGI_OBJS)
	$(LD) $(LFLAGS) $@ $(ADD_USER_CGI_OBJS) -lcrypt -lmenu -lform -lncurses -L. -lmlcgi
	mv $@ $(CGIS_DIR)/$@
	
newUser.cgi:				$(NEW_USER_CGI_OBJS)
	$(LD) $(LFLAGS) $@ $(NEW_USER_CGI_OBJS) -lcrypt -lmenu -lform -lncurses -L. -lmlcgi
	mv $@ $(CGIS_DIR)/$@
	
editUserData.cgi:			$(EDIT_USER_DATA_CGI_OBJS)
	$(LD) $(LFLAGS) $@ $(EDIT_USER_DATA_CGI_OBJS) -lcrypt -lmenu -lform -lncurses -L. -lmlcgi
	mv $@ $(CGIS_DIR)/$@
	
removeUser.cgi:				$(REMOVE_USER_CGI_OBJS)
	$(LD) $(LFLAGS) $@ $(REMOVE_USER_CGI_OBJS) -lcrypt -lmenu -lform -lncurses -L. -lmlcgi
	mv $@ $(CGIS_DIR)/$@
	
inviteUser.cgi:				$(INVITE_USER_CGI_OBJS)
	$(LD) $(LFLAGS) $@ $(INVITE_USER_CGI_OBJS) -lcrypt -lmenu -lform -lncurses -L. -lmlcgi -lsendmail
	mv $@ $(CGIS_DIR)/$@
	
inviteFriend.cgi:			$(INVITE_FRIEND_CGI_OBJS)
	$(LD) $(LFLAGS) $@ $(INVITE_FRIEND_CGI_OBJS) -lcrypt -lmenu -lform -lncurses -L. -lmlcgi -lsendmail
	mv $@ $(CGIS_DIR)/$@
	
getFriendshipInvitation.cgi:		$(GET_FRIENDSHIP_INVITATION_CGI_OBJS)
	$(LD) $(LFLAGS) $@ $(GET_FRIENDSHIP_INVITATION_CGI_OBJS) -lcrypt -lmenu -lform -lncurses -L. -lmlcgi -lsendmail
	mv $@ $(CGIS_DIR)/$@
	
acceptFriendshipInvitation.cgi:		$(ACCEPT_FRIENDSHIP_INVITATION_CGI_OBJS)
	$(LD) $(LFLAGS) $@ $(ACCEPT_FRIENDSHIP_INVITATION_CGI_OBJS) -lcrypt -lmenu -lform -lncurses -L. -lmlcgi -lsendmail
	mv $@ $(CGIS_DIR)/$@
	
rejectFriendshipInvitation.cgi:		$(REJECT_FRIENDSHIP_INVITATION_CGI_OBJS)
	$(LD) $(LFLAGS) $@ $(REJECT_FRIENDSHIP_INVITATION_CGI_OBJS) -lcrypt -lmenu -lform -lncurses -L. -lmlcgi -lsendmail
	mv $@ $(CGIS_DIR)/$@
	
excludeFriend.cgi:			$(EXCLUDE_FRIEND_CGI_OBJS)
	$(LD) $(LFLAGS) $@ $(EXCLUDE_FRIEND_CGI_OBJS) -lcrypt -lmenu -lform -lncurses -L. -lmlcgi -lsendmail
	mv $@ $(CGIS_DIR)/$@
	
getFriends.cgi:				$(GET_FRIENDS_CGI_OBJS)
	$(LD) $(LFLAGS) $@ $(GET_FRIENDS_CGI_OBJS) -lcrypt -lmenu -lform -lncurses -L. -lmlcgi -lsendmail
	mv $@ $(CGIS_DIR)/$@
	
changeUserCategory.cgi:			$(CHANGE_USER_CATEGORY_CGI_OBJS)
	$(LD) $(LFLAGS) $@ $(CHANGE_USER_CATEGORY_CGI_OBJS) -lcrypt -lmenu -lform -lncurses -L. -lmlcgi -lsendmail
	mv $@ $(CGIS_DIR)/$@
	
addParentRelationship.cgi:		$(ADD_PARENT_RELATIONSHIP_CGI_OBJS)
	$(LD) $(LFLAGS) $@ $(ADD_PARENT_RELATIONSHIP_CGI_OBJS) -lcrypt -lmenu -lform -lncurses -L. -lmlcgi -lsendmail
	mv $@ $(CGIS_DIR)/$@
	
removeParentRelationship.cgi:		$(REMOVE_PARENT_RELATIONSHIP_CGI_OBJS)
	$(LD) $(LFLAGS) $@ $(REMOVE_PARENT_RELATIONSHIP_CGI_OBJS) -lcrypt -lmenu -lform -lncurses -L. -lmlcgi -lsendmail
	mv $@ $(CGIS_DIR)/$@
	
editParentRelationship.cgi:		$(EDIT_PARENT_RELATIONSHIP_CGI_OBJS)
	$(LD) $(LFLAGS) $@ $(EDIT_PARENT_RELATIONSHIP_CGI_OBJS) -lcrypt -lmenu -lform -lncurses -L. -lmlcgi -lsendmail
	mv $@ $(CGIS_DIR)/$@
	
getUsers.cgi:				$(GET_USERS_CGI_OBJS)
	$(LD) $(LFLAGS) $@ $(GET_USERS_CGI_OBJS) -lcrypt -lmenu -lform -lncurses -L. -lmlcgi -lsendmail
	mv $@ $(CGIS_DIR)/$@
	
recoveryPassword.cgi:			$(RECOVERY_PASSWORD_CGI_OBJS)
	$(LD) $(LFLAGS) $@ $(RECOVERY_PASSWORD_CGI_OBJS) -lcrypt -lmenu -lform -lncurses -L. -lmlcgi -lsendmail
	mv $@ $(CGIS_DIR)/$@
	
recoveryUserPassword.cgi:		$(RECOVERY_USER_PASSWORD_CGI_OBJS)
	$(LD) $(LFLAGS) $@ $(RECOVERY_USER_PASSWORD_CGI_OBJS) -lcrypt -lmenu -lform -lncurses -L. -lmlcgi -lsendmail
	mv $@ $(CGIS_DIR)/$@
	
changePassword.cgi:			$(CHANGE_PASSWORD_CGI_OBJS)
	$(LD) $(LFLAGS) $@ $(CHANGE_PASSWORD_CGI_OBJS) -lcrypt -lmenu -lform -lncurses -L. -lmlcgi -lsendmail
	mv $@ $(CGIS_DIR)/$@
	
mountFamilyTree.cgi:			$(MOUNT_FAMILY_TREE_CGI_OBJS)
	$(LD) $(LFLAGS) $@ $(MOUNT_FAMILY_TREE_CGI_OBJS) -lcrypt -lmenu -lform -lncurses -L. -lmlcgi -lsendmail
	mv $@ $(CGIS_DIR)/$@
	
clean:
	rm -rf *.o *~ $(BINARIES_DIR)/* $(CGIS_DIR)/* 
#=============================================================================#
#=============================================================================#
