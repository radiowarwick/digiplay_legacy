package org.dps.servicelayer.dto;

import java.util.Date;
import java.util.HashSet;
import java.util.Set;

import javax.persistence.CascadeType;
import javax.persistence.Column;
import javax.persistence.Entity;
import javax.persistence.JoinColumn;
import javax.persistence.JoinTable;
import javax.persistence.ManyToMany;
import javax.persistence.PrePersist;
import javax.persistence.PrimaryKeyJoinColumn;
import javax.persistence.Table;

@Entity
@Table(name="audio")
@PrimaryKeyJoinColumn(name="file_id")
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
	
	//AudioTypeID object
	//Createor object
	
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
	
	@ManyToMany(targetEntity=Album.class, cascade={CascadeType.PERSIST, CascadeType.MERGE})
	@JoinTable(name="audioalbum", 
			joinColumns=@JoinColumn(name="audio_id"), 
			inverseJoinColumns=@JoinColumn(name="album_id"))
	private Set<Album> albums = new HashSet<Album>();
	
	@ManyToMany(targetEntity=Artist.class, cascade={CascadeType.PERSIST, CascadeType.MERGE})
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
	public String getFileType() {
		return fileType;
	}
	/**
	 * @param fileType the fileType to set
	 */
	public void setFileType(String fileType) {
		this.fileType = fileType;
	}

	public void setAlbums(Set<Album> albums) {
		this.albums = albums;
	}

	public Set<Album> getAlbums() {
		return albums;
	}
	
	/**
	 * @return the artists
	 */
	public Set<Artist> getArtists() {
		return artists;
	}

	/**
	 * @param artists the artists to set
	 */
	public void setArtists(Set<Artist> artists) {
		this.artists = artists;
	}
	

}
