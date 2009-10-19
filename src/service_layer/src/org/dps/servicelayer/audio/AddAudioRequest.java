package org.dps.servicelayer.audio;

import javax.xml.bind.annotation.XmlAccessType;
import javax.xml.bind.annotation.XmlAccessorType;
import javax.xml.bind.annotation.XmlElement;

import org.dps.servicelayer.dto.Audio;

@XmlAccessorType(XmlAccessType.NONE)
public class AddAudioRequest {
	
	private Audio audio;
	
	@XmlElement(required = true)
	public Audio getAudio() {
		return audio;
	}

	public void setAudio(Audio audio_) {
		audio = audio_;
	}
	
}
