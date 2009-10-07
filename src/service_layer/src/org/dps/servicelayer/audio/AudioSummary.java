package org.dps.servicelayer.audio;

import java.util.HashSet;
import java.util.Set;

import javax.xml.bind.annotation.XmlAccessType;
import javax.xml.bind.annotation.XmlAccessorType;
import javax.xml.bind.annotation.XmlElement;
import javax.xml.bind.annotation.XmlElementWrapper;

import org.dps.servicelayer.dto.Album;
import org.dps.servicelayer.dto.Artist;
import org.dps.servicelayer.dto.Audio;

@XmlAccessorType(XmlAccessType.NONE)
public class AudioSummary {
	
	private Long fileID;
	
	private Integer sampleLength;
	
	private String title;
	
	private Boolean sustainer;
	
	private Boolean flagged;
	
	private Boolean censor;
	
	private Set<ArtistSummary> artists = new HashSet<ArtistSummary>();
	
	private Set<AlbumSummary> albums = new HashSet<AlbumSummary>();
	
	public AudioSummary() {
		
	}
	public AudioSummary(Audio audio_) {
		this.fileID = audio_.getFileID();
		this.sampleLength = audio_.getSampleLength();
		this.title = audio_.getTitle();
		this.sustainer = audio_.getSustainer();
		this.flagged = audio_.getFlagged();
		this.censor = audio_.getCensor();
		for(Artist artist : audio_.getArtists()) {
			this.artists.add(new ArtistSummary(artist));
		}
		for(Album album : audio_.getAlbums()) {
			this.albums.add(new AlbumSummary(album));
		}
	}
	
	@XmlElement(required = true)
	public Long getFileID() {
		return fileID;
	}
	public void setFileID(Long fileID) {
		this.fileID = fileID;
	}

	@XmlElement(required = true)
	public Integer getSampleLength() {
		return sampleLength;
	}
	public void setSampleLength(Integer sampleLength) {
		this.sampleLength = sampleLength;
	}

	@XmlElement(required = true)
	public String getTitle() {
		return title;
	}
	public void setTitle(String title) {
		this.title = title;
	}

	@XmlElement(required = true)
	public Boolean getSustainer() {
		return sustainer;
	}
	public void setSustainer(Boolean sustainer) {
		this.sustainer = sustainer;
	}

	@XmlElement(required = true)
	public Boolean getFlagged() {
		return flagged;
	}

	public void setFlagged(Boolean flagged) {
		this.flagged = flagged;
	}

	@XmlElement(required = true)
	public Boolean getCensor() {
		return censor;
	}
	public void setCensor(Boolean censor) {
		this.censor = censor;
	}

	@XmlElement(name="artist",required = true)
	@XmlElementWrapper(name="artists", required = true)
	public Set<ArtistSummary> getArtists() {
		return artists;
	}
	public void setArtists(Set<ArtistSummary> artist) {
		this.artists = artist;
	}

	@XmlElement(name="album", required = true)
	@XmlElementWrapper(name="albums", required = true)
	public Set<AlbumSummary> getAlbums() {
		return albums;
	}
	public void setAlbums(Set<AlbumSummary> albums) {
		this.albums = albums;
	}

	@XmlAccessorType(XmlAccessType.NONE)
	private static class ArtistSummary {
		
		private Long artistID;
		
		private String name;
		
		public ArtistSummary() {
			
		}
		public ArtistSummary(Artist artist_) {
			artistID = artist_.getArtistID();
			name = artist_.getName();
		}

		@XmlElement(required = true)
		public Long getArtistID() {
			return artistID;
		}
		public void setArtistID(Long artistID) {
			this.artistID = artistID;
		}

		@XmlElement(required = true)
		public String getName() {
			return name;
		}
		public void setName(String name) {
			this.name = name;
		}
	}
	
	@XmlAccessorType(XmlAccessType.NONE)
	private static class AlbumSummary {
		
		private Long albumID;
		
		private String name;
		
		public AlbumSummary() {
			
		}
		public AlbumSummary(Album album_) {
			albumID = album_.getAlbumID();
			name = album_.getName();
		}
		
		@XmlElement(required = true)
		public Long getAlbumID() {
			return albumID;
		}
		public void setAlbumID(Long albumID) {
			this.albumID = albumID;
		}

		@XmlElement(required = true)
		public String getName() {
			return name;
		}
		public void setName(String name) {
			this.name = name;
		}
	}
	
}
