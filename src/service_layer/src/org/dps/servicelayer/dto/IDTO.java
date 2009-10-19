package org.dps.servicelayer.dto;

public interface IDTO {

	Audio getAudio(Long fileID_);

	Artist getArtist(String name_);

	Artist getArtist(Long artistID_);
	
	Album getAlbum(String name_);
	
	Album getAlbum(Long albumID_);
	
	File getFile(Long fileID_);
	
	<T extends Object> T saveOrUpdate(T item_);
	
	<T extends Object> T delete(T item_);

}
