
$(document).ready(function() {
    $('#music-catalog').DataTable( {
        "ajax": "music-repository.json",
        columns: [
            { "title": "File Name", "data": "file_name", "visible": false},
            { "title": "File Location", "data": "file_location", "visible": false},
            { "title": "Title", "data": "title" },
            { "title": "Artist", "data": "artist" },
            { "title": "Album", "data": "album" },
            { "title": "Year", "data": "year" },
            { "title": "Track", "data": "track" },
            { "title": "Genre", "data": "genre" },
            { "title": "Bitrate", "data": "bitrate"},
            { "title": "Sample Rate", "data": "sample_rate"},
            { "title": "Channels", "data": "channels"},
            // { "title": "Time", "data": "time"},
            { "title": "Time (m)", "data": "length_in_minutes", "visible": false},
            { "title": "Time (s)", "data": "length_in_seconds", "visible": false}
        ]
    } );
} );
