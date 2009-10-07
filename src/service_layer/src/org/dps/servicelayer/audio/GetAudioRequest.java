package org.dps.servicelayer.audio;

import javax.xml.bind.annotation.XmlAccessType;
import javax.xml.bind.annotation.XmlAccessorType;
import javax.xml.bind.annotation.XmlElement;

@XmlAccessorType(XmlAccessType.NONE)
public class GetAudioRequest {
	long audioID;

	@XmlElement(required = true)
	public long getAudioID() {
		return audioID;
	}
	public void setAudioID(long audioID) {
		this.audioID = audioID;
	}
	
}
