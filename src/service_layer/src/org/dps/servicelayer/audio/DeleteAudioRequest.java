package org.dps.servicelayer.audio;

import javax.xml.bind.annotation.XmlAccessType;
import javax.xml.bind.annotation.XmlAccessorType;
import javax.xml.bind.annotation.XmlElement;

@XmlAccessorType(XmlAccessType.NONE)
public class DeleteAudioRequest {
	private Long audioID;

	@XmlElement(required = true)
	public Long getAudioID() {
		return audioID;
	}
	public void setAudioID(Long audioID) {
		this.audioID = audioID;
	}
}
