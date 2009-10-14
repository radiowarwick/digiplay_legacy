package org.dps.servicelayer.audio;

import javax.xml.bind.annotation.XmlAccessType;
import javax.xml.bind.annotation.XmlAccessorType;
import javax.xml.bind.annotation.XmlElement;

import org.dps.servicelayer.dto.Audio;

@XmlAccessorType(XmlAccessType.NONE)
public class AddAudioArtistResponse {
	
	private Audio _audio;
	
	public AddAudioArtistResponse() {
		
	}
	public AddAudioArtistResponse(AddAudioArtistRequest request_) {
		
	}
	
	@XmlElement(required = true)
	public Audio getAudio() {
		return _audio;
	}
	public void setAudio(Audio audio_) {
		_audio = audio_;
	}

}
