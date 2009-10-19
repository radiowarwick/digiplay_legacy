package org.dps.servicelayer.audio;

import javax.xml.bind.annotation.XmlAccessType;
import javax.xml.bind.annotation.XmlAccessorType;
import javax.xml.bind.annotation.XmlElement;

@XmlAccessorType(XmlAccessType.NONE)
public class AddAudioAlbumRequest {
	private Long _audioID;
	
	private Long _albumID;

	@XmlElement(required = true)
	public Long getAudioID() {
		return _audioID;
	}
	public void setAudioID(Long audioID_) {
		_audioID = audioID_;
	}
	
	@XmlElement(required = true)
	public Long getAlbumID() {
		return _albumID;
	}
	public void setAlbumID(Long albumID_) {
		_albumID = albumID_;
	}
}
