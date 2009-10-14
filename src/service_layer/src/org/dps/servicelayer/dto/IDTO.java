package org.dps.servicelayer.dto;

public interface IDTO {

	Audio getAudio(Long fileID_);

	Artist getArtist(String name_);

	Artist getArtist(Long artistID_);
	
	<T extends Object> T saveOrUpdate(T object_);

}
