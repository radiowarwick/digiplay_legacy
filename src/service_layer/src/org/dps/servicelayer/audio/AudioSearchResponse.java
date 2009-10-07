package org.dps.servicelayer.audio;

import java.util.List;

import javax.xml.bind.annotation.XmlAccessType;
import javax.xml.bind.annotation.XmlAccessorType;
import javax.xml.bind.annotation.XmlElement;
import javax.xml.bind.annotation.XmlElementWrapper;

@XmlAccessorType(XmlAccessType.NONE)
public class AudioSearchResponse {

	List<AudioSummary> audios;
	
	public AudioSearchResponse() {
		
	}
	public AudioSearchResponse(AudioSearchRequest request_) {
		
	}
	
	@XmlElement(name="audio", required = true)
	@XmlElementWrapper(name="audios", required = true)
	public List<AudioSummary> getAudios() {
		return audios;
	}
	public void setAudios(List<AudioSummary> audios) {
		this.audios = audios;
	}
}
