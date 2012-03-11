//==========================  Open Steamworks  ================================
//
// This file is part of the Open Steamworks project. All individuals associated
// with this project do not claim ownership of the contents
// 
// The code, comments, and all related files, projects, resources,
// redistributables included with this project are Copyright Valve Corporation.
// Additionally, Valve, the Valve logo, Half-Life, the Half-Life logo, the
// Lambda logo, Steam, the Steam logo, Team Fortress, the Team Fortress logo,
// Opposing Force, Day of Defeat, the Day of Defeat logo, Counter-Strike, the
// Counter-Strike logo, Source, the Source logo, and Counter-Strike Condition
// Zero are trademarks and or registered trademarks of Valve Corporation.
// All other trademarks are property of their respective owners.
//
//=============================================================================

#ifndef ISTEAMREMOTESTORAGE006_H
#define ISTEAMREMOTESTORAGE006_H
#ifdef _WIN32
#pragma once
#endif

#include "SteamTypes.h"
#include "RemoteStorageCommon.h"

//-----------------------------------------------------------------------------
// Purpose: Functions for accessing, reading and writing files stored remotely 
//			and cached locally
//-----------------------------------------------------------------------------
abstract_class ISteamRemoteStorage006
{
public:
	// NOTE
	//
	// Filenames are case-insensitive, and will be converted to lowercase automatically.
	// So "foo.bar" and "Foo.bar" are the same file, and if you write "Foo.bar" then
	// iterate the files, the filename returned will be "foo.bar".
	//

	// file operations
	virtual bool	FileWrite( const char *pchFile, const void *pvData, int32 cubData ) = 0;
	virtual int32	FileRead( const char *pchFile, void *pvData, int32 cubDataToRead ) = 0;
	virtual bool	FileForget( const char *pchFile ) = 0;
	virtual bool	FileDelete( const char *pchFile ) = 0;
	virtual SteamAPICall_t FileShare( const char *pchFile ) = 0;
	virtual bool	SetSyncPlatforms( const char *pchFile, ERemoteStoragePlatform eRemoteStoragePlatform ) = 0;

	// file information
	virtual bool	FileExists( const char *pchFile ) = 0;
	virtual bool	FilePersisted( const char *pchFile ) = 0;
	virtual int32	GetFileSize( const char *pchFile ) = 0;
	virtual int64	GetFileTimestamp( const char *pchFile ) = 0;
	virtual ERemoteStoragePlatform GetSyncPlatforms( const char *pchFile ) = 0;

	// iteration
	virtual int32 GetFileCount() = 0;
	virtual const char *GetFileNameAndSize( int iFile, int32 *pnFileSizeInBytes ) = 0;

	// configuration management
	virtual bool GetQuota( int32 *pnTotalBytes, int32 *puAvailableBytes ) = 0;
	virtual bool IsCloudEnabledForAccount() = 0;
	virtual bool IsCloudEnabledForApp() = 0;
	virtual void SetCloudEnabledForApp( bool bEnabled ) = 0;

	// user generated content
	virtual SteamAPICall_t UGCDownload( UGCHandle_t hContent ) = 0; // Returns a RemoteStorageDownloadUGCResult_t callback
	virtual bool GetUGCDownloadProgress( UGCHandle_t hContent, uint32 *puDownloadedBytes, uint32 *puTotalBytes ) = 0;
	virtual bool	GetUGCDetails( UGCHandle_t hContent, AppId_t *pnAppID, char **ppchName, int32 *pnFileSizeInBytes, CSteamID *pSteamIDOwner ) = 0;
	virtual int32	UGCRead( UGCHandle_t hContent, void *pvData, int32 cubDataToRead ) = 0;

	// user generated content iteration
	virtual int32	GetCachedUGCCount() = 0;
	virtual	UGCHandle_t GetCachedUGCHandle( int32 iCachedContent ) = 0;

	virtual SteamAPICall_t PublishWorkshopFile( const char *cszFileName, const char *cszPreviewFileName, AppId_t nConsumerAppId, const char *cszTitle, const char *cszDescription, ERemoteStoragePublishedFileVisibility eRemoteStoragePublishedFileVisibility, SteamParamStringArray_t *pTags, EWorkshopFileType eWorkshopFileType ) = 0;
	virtual JobID_t CreatePublishedFileUpdateRequest( UGCHandle_t hPublishedFile ) = 0;
	virtual bool UpdatePublishedFileFile( JobID_t hUpdateRequest, const char *cszFile ) = 0;
	virtual bool UpdatePublishedFilePreviewFile( JobID_t hUpdateRequest, const char *cszPreviewFile ) = 0;
	virtual bool UpdatePublishedFileTitle( JobID_t hUpdateRequest, const char *cszTitle ) = 0;
	virtual bool UpdatePublishedFileDescription( JobID_t hUpdateRequest, const char *cszDescription ) = 0;
	virtual bool UpdatePublishedFileVisibility( JobID_t hUpdateRequest, ERemoteStoragePublishedFileVisibility eVisibility ) = 0;
	virtual bool UpdatePublishedFileTags( JobID_t hUpdateRequest, SteamParamStringArray_t *pTags ) = 0;
	virtual SteamAPICall_t CommitPublishedFileUpdate( JobID_t hUpdateRequest ) = 0;

	virtual SteamAPICall_t GetPublishedFileDetails( UGCHandle_t hPublishedFile ) = 0;
	virtual SteamAPICall_t DeletePublishedFile( UGCHandle_t hPublishedFile ) = 0;
	virtual SteamAPICall_t EnumerateUserPublishedFiles( uint32 uStartIndex ) = 0;
	virtual SteamAPICall_t SubscribePublishedFile( UGCHandle_t hPublishedFile ) = 0;
	virtual SteamAPICall_t EnumerateUserSubscribedFiles( uint32 uStartIndex ) = 0;
	virtual SteamAPICall_t UnsubscribePublishedFile( UGCHandle_t hPublishedFile ) = 0;
};

#endif // ISTEAMREMOTESTORAGE006_H