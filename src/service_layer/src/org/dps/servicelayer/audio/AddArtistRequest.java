package org.dps.servicelayer.audio;

import javax.xml.bind.annotation.XmlAccessType;
import javax.xml.bind.annotation.XmlAccessorType;
import javax.xml.bind.annotation.XmlElement;

import org.dps.servicelayer.dto.Artist;

@XmlAccessorType(XmlAccessType.NONE)
public class AddArtistRequest {
	
	private Artist _artist;

	@XmlElement(required = true)
	public Artist getArtist() {
		return _artist;
	}
	public void setArtist(Artist artist_) {
		_artist = artist_;
	}
}
