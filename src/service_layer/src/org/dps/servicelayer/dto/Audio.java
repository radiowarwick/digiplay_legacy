package org.dps.servicelayer.dto;

import java.util.HashSet;
import java.util.Set;

import javax.persistence.CascadeType;
import javax.persistence.Column;
import javax.persistence.Entity;
import javax.persistence.FetchType;
import javax.persistence.JoinColumn;
import javax.persistence.JoinTable;
import javax.persistence.ManyToMany;
import javax.persistence.ManyToOne;
import javax.persistence.OneToMany;
import javax.persistence.OneToOne;
import javax.persistence.PrimaryKeyJoinColumn;
import javax.persistence.Table;
import javax.xml.bind.annotation.XmlAccessType;
import javax.xml.bind.annotation.XmlAccessorType;
import javax.xml.bind.annotation.XmlElement;
import javax.xml.bind.annotation.XmlElementWrapper;

@Entity
@Table(name="audio")
@PrimaryKeyJoinColumn(name="file_id")
@XmlAccessorType(XmlAccessType.NONE)
public class Audio extends File {
	
	@Column(name="md5")
	private String md5;
	
	@Column(name="length_smpl")
	private Integer sampleLength;
	
	@Column(name="start_smpl")
	private Integer sampleStart;
	
	@Column(name="end_smpl")
	private Integer sampleEnd;
	
	@Column(name="intro_smpl")
	private Integer sampleIntro;
	
	@Column(name="extro_smpl")
	private Integer sampleExtro;
	
	@ManyToOne(optional=false)
	@JoinColumn(name="audio_type_id", nullable=false, insertable=false, updatable=false)
	private AudioType audioType;
	
	@ManyToOne
	@JoinColumn(name="creator_id")
	private User creator;
	
	@Column(name="import_date")
	private Integer importDate;
	
	@Column(name="title")
	private String title;
	
	@Column(name="sustainer")
	private Boolean sustainer;
	
	@Column(name="flagged")
	private Boolean flagged;
	
	@Column(name="censor")
	private Boolean censor;
	
	@Column(name="filetype")
	private String fileType;
	
	@ManyToMany(targetEntity=Album.class, cascade={CascadeType.PERSIST, CascadeType.MERGE}, fetch=FetchType.LAZY)
	@JoinTable(name="audioalbum", 
			joinColumns=@JoinColumn(name="audio_id"), 
			inverseJoinColumns=@JoinColumn(name="album_id"))
	private Set<Album> albums = new HashSet<Album>();
	
	@ManyToMany(targetEntity=Artist.class, cascade={CascadeType.PERSIST, CascadeType.MERGE}, fetch=FetchType.LAZY)
	@JoinTable(name="audioartist", 
			joinColumns=@JoinColumn(name="audio_id"), 
			inverseJoinColumns=@JoinColumn(name="artist_id"))
	private Set<Artist> artists = new HashSet<Artist>();

	public String toString() {
		return getFileID() + ":" + title;
	}

	/**
	 * @return the md5
	 */
	@XmlElement(required = true)
	public String getMd5() {
		return md5;
	}
	/**
	 * @param md5 the md5 to set
	 */
	public void setMd5(String md5) {
		this.md5 = md5;
	}
	/**
	 * @return the sampleLength
	 */
	@XmlElement(required = true)
	public Integer getSampleLength() {
		return sampleLength;
	}
	/**
	 * @param sampleLength the sampleLength to set
	 */
	public void setSampleLength(Integer sampleLength) {
		this.sampleLength = sampleLength;
	}
	/**
	 * @return the sampleStart
	 */
	@XmlElement(required = true)
	public Integer getSampleStart() {
		return sampleStart;
	}
	/**
	 * @param sampleStart the sampleStart to set
	 */
	public void setSampleStart(Integer sampleStart) {
		this.sampleStart = sampleStart;
	}
	/**
	 * @return the sampleEnd
	 */
	@XmlElement(required = true)
	public Integer getSampleEnd() {
		return sampleEnd;
	}
	/**
	 * @param sampleEnd the sampleEnd to set
	 */
	public void setSampleEnd(Integer sampleEnd) {
		this.sampleEnd = sampleEnd;
	}
	/**
	 * @return the sampleIntro
	 */
	@XmlElement(required = true)
	public Integer getSampleIntro() {
		return sampleIntro;
	}
	/**
	 * @param sampleIntro the sampleIntro to set
	 */
	public void setSampleIntro(Integer sampleIntro) {
		this.sampleIntro = sampleIntro;
	}
	/**
	 * @return the sampleExtro
	 */
	@XmlElement(required = true)
	public Integer getSampleExtro() {
		return sampleExtro;
	}
	/**
	 * @param sampleExtro the sampleExtro to set
	 */
	public void setSampleExtro(Integer sampleExtro) {
		this.sampleExtro = sampleExtro;
	}
	/**
	 * @return the importDate
	 */
	@XmlElement(required = true)
	public Integer getImportDate() {
		return importDate;
	}
	/**
	 * @param importDate the importDate to set
	 */
	public void setImportDate(Integer importDate) {
		this.importDate = importDate;
	}
	/**
	 * @return the title
	 */
	@XmlElement(required = true)
	public String getTitle() {
		return title;
	}
	/**
	 * @param title the title to set
	 */
	public void setTitle(String title) {
		this.title = title;
	}
	/**
	 * @return the sustainer
	 */
	@XmlElement(required = true)
	public Boolean getSustainer() {
		return sustainer;
	}
	/**
	 * @param sustainer the sustainer to set
	 */
	public void setSustainer(Boolean sustainer) {
		this.sustainer = sustainer;
	}
	/**
	 * @return the flagged
	 */
	@XmlElement(required = true)
	public Boolean getFlagged() {
		return flagged;
	}
	/**
	 * @param flagged the flagged to set
	 */
	public void setFlagged(Boolean flagged) {
		this.flagged = flagged;
	}
	/**
	 * @return the censor
	 */
	@XmlElement(required = true)
	public Boolean getCensor() {
		return censor;
	}
	/**
	 * @param censor the censor to set
	 */
	public void setCensor(Boolean censor) {
		this.censor = censor;
	}
	/**
	 * @return the fileType
	 */
	@XmlElement(required = true)
	public String getFileType() {
		return fileType;
	}
	/**
	 * @param fileType the fileType to set
	 */
	public void setFileType(String fileType) {
		this.fileType = fileType;
	}

	@XmlElement(name="album", required = true)
	@XmlElementWrapper(name="albums", required = true)
	public Set<Album> getAlbums() {
		return albums;
	}
	public void setAlbums(Set<Album> albums) {
		this.albums = albums;
	}

	
	/**
	 * @return the artists
	 */
	@XmlElement(name="artist", required = true)
	@XmlElementWrapper(name="artists", required = true)
	public Set<Artist> getArtists() {
		return artists;
	}

	/**
	 * @param artists the artists to set
	 */
	public void setArtists(Set<Artist> artists) {
		this.artists = artists;
	}
	
	public void setAudioType(AudioType audioType) {
		this.audioType = audioType;
	}

	public AudioType getAudioType() {
		return audioType;
	}

	public void setCreator(User creator) {
		this.creator = creator;
	}

	public User getCreator() {
		return creator;
	}

	public void makeSafe() {
		getAlbums().size();
		getArtists().size();
	}
	

}
