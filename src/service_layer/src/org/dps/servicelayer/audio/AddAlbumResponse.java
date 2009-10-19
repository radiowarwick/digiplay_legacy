package org.dps.servicelayer.audio;

import javax.xml.bind.annotation.XmlAccessType;
import javax.xml.bind.annotation.XmlAccessorType;
import javax.xml.bind.annotation.XmlElement;

import org.dps.servicelayer.dto.Album;

@XmlAccessorType(XmlAccessType.NONE)
public class AddAlbumResponse {
	
	public AddAlbumResponse() {
		
	}
	public AddAlbumResponse(AddAlbumRequest request_) {
		
	}
	
	@XmlElement(required = true)
	private Album _Album;

	public Album getAlbum() {
		return _Album;
	}

	public void setAlbum(Album album_) {
		_Album = album_;
	}
}
