package org.dps.servicelayer.audio;

import javax.xml.bind.annotation.XmlElement;

import org.dps.servicelayer.dto.Audio;

public class AddAudioAlbumResponse {
	private Audio _audio;
	
	public AddAudioAlbumResponse() {
		
	}
	public AddAudioAlbumResponse(AddAudioAlbumRequest request_) {
		
	}
	
	@XmlElement(required = true)
	public Audio getAudio() {
		return _audio;
	}
	public void setAudio(Audio audio_) {
		_audio = audio_;
	}
}
