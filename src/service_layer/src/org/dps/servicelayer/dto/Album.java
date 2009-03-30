package org.dps.servicelayer.dto;

import java.util.HashSet;
import java.util.Set;

import javax.persistence.CascadeType;
import javax.persistence.Column;
import javax.persistence.Entity;
import javax.persistence.FetchType;
import javax.persistence.GeneratedValue;
import javax.persistence.GenerationType;
import javax.persistence.Id;
import javax.persistence.JoinTable;
import javax.persistence.ManyToMany;
import javax.persistence.Table;

import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

@Entity
@Table(name="album")
public class Album extends Audit {

	final static Logger LOGGER = LoggerFactory.getLogger(Album.class);
	
	@Column(name="album_id")
	@Id
	@GeneratedValue(strategy=GenerationType.AUTO)
	private Long albumID;
	
	@Column(name="name")
	private String name;
	
	@ManyToMany(cascade={CascadeType.PERSIST, CascadeType.MERGE},
			mappedBy="albums",
			targetEntity= Audio.class)
	private Set<Audio> audios = new HashSet<Audio>();
	
	public String toString() {
		return albumID + ":" + name;
	}
	
	/**
	 * @return the name
	 */
	public String getName() {
		return name;
	}

	/**
	 * @param name the name to set
	 */
	public void setName(String name) {
		this.name = name;
	}

	/**
	 * @return the albumID
	 */
	public Long getAlbumID() {
		return albumID;
	}

	/**
	 * @param albumID the albumID to set
	 */
	public void setAlbumID(Long albumID) {
		this.albumID = albumID;
	}

	/**
	 * @return the audio
	 */
	public Set<Audio> getAudio() {
		return audios;
	}

	/**
	 * @param audio the audio to set
	 */
	public void setAudio(Set<Audio> audio) {
		this.audios = audio;
	}	
	
}
