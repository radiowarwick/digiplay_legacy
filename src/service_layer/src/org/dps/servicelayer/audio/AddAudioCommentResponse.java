package org.dps.servicelayer.audio;

import javax.xml.bind.annotation.XmlAccessType;
import javax.xml.bind.annotation.XmlAccessorType;
import javax.xml.bind.annotation.XmlElement;

@XmlAccessorType(XmlAccessType.NONE)
public class AddAudioCommentResponse {
	private Long _audioID;
	private String _comment;
	
	public AddAudioCommentResponse() {
		
	}
	public AddAudioCommentResponse(AddAudioCommentRequest request) {
		_audioID = request.getAudioID();
		//TODO: Maybe this should be actually set manually in case it is changed by the save command.
		_comment = request.getComment();
	}
	
	@XmlElement(required = true)
	public Long getAudioID() {
		return _audioID;
	}
	public void setAudioID(Long audioID_) {
		_audioID = audioID_;
	}
	@XmlElement(required = true)
	public String getComment() {
		return _comment;
	}
	public void setComment(String comment_) {
		_comment = comment_;
	}
}
