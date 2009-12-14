#pragma once

// move these to interfaces eventually
extern ISteamClient *steamClient; // this is exposed
extern ISteamUser *steamUser;
extern ISteamUtils *steamUtils; // etc..

// globals so that GetInterfaces and SteamAPI_InitInternal can access them
// best to have an array of these, but i'm too tried to fully implement something like that
extern char steamClientVer[ 30 ];
extern char steamUserVer[ 30 ];
extern char steamUtilsVer[ 30 ]; // etc..

#define EXPORT_CURRENT_VERSION(ICLASS, EXPORT) \
	S_API ICLASS * STEAM_CALL EXPORT();

#define DEFINE_CURRENT_VERSION(IFACE, VERSION, ICLASS, EXPORT) \
	const char* IFACE##_VERSION = IFACE##_INTERFACE_VERSION_##VERSION; \
	void* IFACE##_PTR = NULL; \
	S_API ICLASS* STEAM_CALL EXPORT() { return (ICLASS *) IFACE##_PTR; } \

#define TRYGET_CURRENT_VERSION(IFACE, VMETHOD) \
	IFACE##_PTR = (void *)steamclient->VMETHOD(user, pipe, IFACE##_VERSION); \
	if( IFACE##_PTR == NULL ) return false;

#define TRYGET_CURRENT_VERSION_PIPE(IFACE, VMETHOD) \
	IFACE##_PTR = (void *)steamclient->VMETHOD(pipe, IFACE##_VERSION); \
	if( IFACE##_PTR == NULL ) return false;

bool LoadInterfaces();

S_API ISteamClient* STEAM_CALL SteamClient();

EXPORT_CURRENT_VERSION(ISteamUser,					SteamUser);
EXPORT_CURRENT_VERSION(ISteamFriends,				SteamFriends);
EXPORT_CURRENT_VERSION(ISteamUtils,					SteamUtils);
EXPORT_CURRENT_VERSION(ISteamMatchmaking,			SteamMatchmaking);
EXPORT_CURRENT_VERSION(ISteamUserStats,				SteamUserStats);
EXPORT_CURRENT_VERSION(ISteamApps,					SteamApps);
EXPORT_CURRENT_VERSION(ISteamNetworking,			SteamNetworking);
EXPORT_CURRENT_VERSION(ISteamMatchmakingServers,	SteamMatchmakingServers);
EXPORT_CURRENT_VERSION(ISteamRemoteStorage,			SteamRemoteStorage);