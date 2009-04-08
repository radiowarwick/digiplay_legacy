package org.dps.servicelayer.dto;

import java.util.HashSet;
import java.util.Set;

import javax.persistence.CascadeType;
import javax.persistence.Column;
import javax.persistence.Entity;
import javax.persistence.GeneratedValue;
import javax.persistence.GenerationType;
import javax.persistence.Id;
import javax.persistence.ManyToMany;
import javax.persistence.Table;

import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

@Entity
@Table(name="artist")
public class Artist extends Audit  {
	
	@Column(name="artist_id")
	@Id
	@GeneratedValue(strategy=GenerationType.AUTO)
	private Long artistID;
	
	@Column(name="name")
	private String name;
	
	@ManyToMany(cascade={CascadeType.PERSIST, CascadeType.MERGE},
			mappedBy="artists",
			targetEntity= Audio.class)
	private Set<Audio> audios = new HashSet<Audio>();
	
	public String toString() {
		return artistID + ":" + name;
	}
	
	/**
	 * @return the album_id
	 */
	public Long getArtistID() {
		return artistID;
	}
	/**
	 * @param album_id the album_id to set
	 */
	public void setArtistID(Long album_id) {
		this.artistID = album_id;
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
	 * @return the audios
	 */
	public Set<Audio> getAudios() {
		return audios;
	}
	/**
	 * @param audios the audios to set
	 */
	public void setAudios(Set<Audio> audios) {
		this.audios = audios;
	}
	
	
}
