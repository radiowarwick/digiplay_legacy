package org.dps.servicelayer.audio;

import javax.xml.bind.annotation.XmlAccessType;
import javax.xml.bind.annotation.XmlAccessorType;
import javax.xml.bind.annotation.XmlElement;

@XmlAccessorType(XmlAccessType.NONE)
public class AddAudioArtistRequest {
	
	private Long _audioID;
	
	private Long _artistID;

	@XmlElement(required = true)
	public Long getAudioID() {
		return _audioID;
	}
	public void setAudioID(Long audioID_) {
		_audioID = audioID_;
	}
	
	@XmlElement(required = true)
	public Long getArtistID() {
		return _artistID;
	}
	public void setArtistID(Long artistID_) {
		_artistID = artistID_;
	}
}
